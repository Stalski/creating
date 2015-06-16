<?php

/**
 * @file
 * Token integration for the Creating webshop.
 */
/**
 * Implements hook_token_info().
 */
function creatingideas_token_info() {
  $info = array();
  $info['tokens']['commerce-order']['order-summary'] = array(
    'name' => t('Order Summary'),
    'description' => t('The summary of the order.'),
  );

  return $info;
}

/**
 * Implements hook_tokens().
 */
function creatingideas_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $replacements = array();

  if ($type == 'commerce-order' && !empty($data['commerce-order'])) {
    $order = $data['commerce-order'];

    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'order-summary':
          $output = entity_view('commerce_order', array($order->order_id => $order), 'customer', NULL, TRUE);
          $replacements[$original] = drupal_render($output);
          break;
      }
    }
  }

  return $replacements;
}