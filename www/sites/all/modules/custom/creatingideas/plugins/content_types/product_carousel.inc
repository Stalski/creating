<?php

$plugin = array(
  'title' => t('Content pane for Product carousels'),
  'single' => TRUE,
  'title' => t('Creating Product carousel'),
  'description' => t('Custom widgets for the Creating website.'),
  'category' => t('Creating Widgets'),
);


/**
 * Render a block with all main taxonomy vocabulary lists.
 */
function creatingideas_product_carousel_content_type_render($subtype, $conf, $panel_args, $context) {

  // Build the content type block.
  $block = new stdClass();
  $block->module  = 'creatingideas';
  $block->delta   = 'tree';
  $block->title   = t('Creating Product Carousel');

  // Prepare query.
  $query = db_select('node', 'n');
  $query->innerJoin("nodequeue_nodes", "nn", " n.nid = nn.nid ");
  $query->innerJoin("nodequeue_queue", "nq", " nq.qid = nn.qid AND nq.name = 'fabric_carousel' ");
  $query->innerJoin("field_data_field_products", "fdfp", " fdfp.entity_id = n.nid ");
  $query->fields('n', array('nid', 'title'));
  $query->fields('fdfp', array('field_products_product_id'));
  $query->condition('n.status', '1');
  $query->orderBy("nn.position", "ASC");
  $result = $query->execute();

  $items = array();
  foreach ($result as $row) {
    $product = commerce_product_load($row->field_products_product_id);
    $products = array($product);
    $product_ids = array($product->product_id);

    // Image.
    $image_items = field_get_items('commerce_product', $product, 'field_bg_image');

    // Price.
    $price_items = field_get_items('commerce_product', $product, 'commerce_price');
    $price_html = commerce_currency_format($price_items[0]['amount'], $price_items[0]['currency_code'], $product);

    // Add to cart.
    $line_item = commerce_product_line_item_new($product, 1, 0, array(), 'product');
    $line_item->data['context']['product_ids'] = $product_ids;
    $line_item->data['context']['add_to_cart_combine'] = TRUE;
    $line_item->data['context']['show_single_product_attributes'] = TRUE;
    // Generate a form ID for this add to cart form.
    $form_id = commerce_cart_add_to_cart_form_id($product_ids);
    $cart_form = drupal_get_form($form_id, $line_item, FALSE, array());
    $message = '<div class="full-price">' . $price_html . '</div>' . drupal_render($cart_form);

    $items[] = array(
      'title' => l(check_plain($row->title), "node/" . $row->nid, array(
        'attributes' => array(),
      )),
      'message' => $message,
      'image' => theme('image_style', array(
        'uri' => $image_items[0]['uri'],
        'path' => $image_items[0]['uri'],
        'style_name' => 'full_width',
       )),
    );
  }

  if (!empty($items)) {
    $block->content = array(
      '#theme' => 'creatingideas_product_carousel',
      '#items' => $items,
    );
  }

  return $block;

}

/**
 * Returns an edit form for custom type settings.
 */
function creatingideas_product_carousel_content_type_edit_form($form, &$form_state) {
  // Empty so that we can have title override.
  return $form;
}

/**
 * Submit handler for Creating Product Category Tree settings.
 */
function creatingideas_product_carousel_content_type_edit_form_submit($form, &$form_state) {

}

/**
 * Returns the administrative title for a type.
 */
function creatingideas_product_carousel_content_type_admin_title($subtype, $conf, $context) {
  return t('Creating Product Carousel');
}

