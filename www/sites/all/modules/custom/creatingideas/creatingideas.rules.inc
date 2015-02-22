<?php

/**
 * @file
 * Rules integration.
 */

/**
 * Implementation of hook_rules_action_info()
 */
function creatingideas_rules_action_info(){
  $actions = array();
  $actions['creatingideas_volume_discount_amount'] = array(
    'label' => t('Volume Discount Amount'),
    'group' => t('Commerce Discount'),
    'parameter' => array(
      'entity' => array(
        'label' => t('Entity'),
        'type' => 'entity',
        'wrapped' => TRUE,
      ),
      'commerce_discount' => array(
        'label' => t('Commerce Discount'),
        'type' => 'token',
        'options list' => 'commerce_discount_entity_list',
      )
    ),
    'base' => 'creatingideas_volume_discount_amount',
  );
  $actions['creatingideas_stock_decrease_by_calculated_value'] = array(
    'label' => t('Decrease the product stock level, given a line item and calculated value'),
    'group' => t('Commerce Stock (ss)'),
    'parameter' => array(
      'commerce_line_item' => array(
        'type' => 'commerce_line_item',
        'label' => t('Line item'),
      ),
      'calculated_quantity' => array(
        'type' => 'integer',
        'label' => t('Integer'),
      ),
    ),
  );
  return $actions;
}

/**
 * Substracts from stock the sold amount in a line item.
 * This action rule is based on commerce_ss_decrease_by_line_item with some
 * overrides.
 * Currently:
 *  - All other cases are a 1-1 relation between quantity and stock amount.
 *  - The product stock level is tracked by creating a new revision.
 *
 * @param $line_item
 *   A line item object.
 * @param $calculated_quantity
 *   A Integer.
 */
function creatingideas_stock_decrease_by_calculated_value($line_item) {
  if (in_array($line_item->type, commerce_product_line_item_types())) {
    // The product SKU that will have its stock level adjusted.
    $sku = $line_item->line_item_label;
    $product = commerce_product_load_by_sku($sku);
    if (commerce_ss_product_type_enabled($product->type)) {
      if (!(commerce_ss_product_type_override_enabled($product->type)
          && isset($product->commerce_stock_override['und']) && $product->commerce_stock_override['und'][0]['value'] == 1)) {

        $qty = $line_item->quantity;
        // Subtract the sold amount from the available stock level.
        module_load_include('inc', 'commerce_ss', 'commerce_ss.rules');

        $wrapper = entity_metadata_wrapper('commerce_product', $product);

        $new_stock = $wrapper->commerce_stock->value() - $qty;
        $wrapper->commerce_stock->set($new_stock);
        $result = $wrapper->save();

        // @todo should this be moved to the
        if ($result) {
          watchdog('commerce_stock', 'Modified stock level of product %sku by %amount', array('%sku' => $product->sku, '%amount' => -$qty));
        }
        else {
          watchdog('commerce_stock', 'Failed attempt to modify stock level of product %sku by %amount', array('%sku' => $product->sku, '%amount' => -$qty), WATCHDOG_ERROR);
        }

      }
    }
  }
}

/**
 * Rules action: Apply volume discount amount discount.
 */
function creatingideas_volume_discount_amount(EntityDrupalWrapper $wrapper, $discount_name) {

  module_load_include("inc", "commerce_discount", "commerce_discount.rules");
  $discount_wrapper = entity_metadata_wrapper('commerce_discount', $discount_name);

  // Exit if there are no line items or the wrapper doesn't contain
  // the commerce_discounts property.
  if (!$wrapper->commerce_line_items->value() || !$wrapper->__isset('commerce_discounts')) {
    return;
  }

  // Set reference to the discount.
  // @todo: It doesn't work with the wrapper.
  $order = $wrapper->value();
  $delta = $wrapper->commerce_discounts->count();
  $order->commerce_discounts[LANGUAGE_NONE][$delta]['target_id'] = $discount_wrapper->discount_id->value();

  $calculated_discount = 0;
  // Loop the line items of the order and calculate the total discount.
  foreach ($wrapper->commerce_line_items as $line_item_wrapper) {

    $new_total = _creatingideas_calculate_line_item_total_price($line_item_wrapper);
    if (isset($new_total)) {
      $price = commerce_price_wrapper_value($line_item_wrapper, 'commerce_total', TRUE);
      $calculated_discount += $price['amount'] - $new_total;
    }
  }

  if ($calculated_discount) {
    $discount_amount = array(
      'amount' => $calculated_discount * -1,
      'currency_code' => $wrapper->commerce_order_total->currency_code->value(),
    );

    // Modify the existing discount line item or add a new one if that fails.
    if (!commerce_discount_set_existing_line_item_price($wrapper, $discount_name, $discount_amount)) {
      commerce_discount_add_line_item($wrapper, $discount_name, $discount_amount);
    }

    // Update the total order price, for the next rules condition (if any).
    commerce_order_calculate_total($order);
  }

}
