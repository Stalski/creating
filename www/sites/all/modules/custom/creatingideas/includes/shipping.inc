<?php

/**
 * @file
 * Shipping methods and service callbacks.
 */

/**
 * Callback for the free flat rate service.
 */
function creatingideas_rate_free($shipping_service, $order) {
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
  return array(
    'amount' => 0,
    'currency_code' => $order_wrapper->commerce_order_total->currency_code->value(),
    'data' => array(),
  );
}

/**
 * Callback for the 2.50 euro flat rate service.
 */
function creatingideas_rate_250($shipping_service, $order) {
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
  return array(
    'amount' => variable_get('creating_simple_post_flat_rate', 250),
    'currency_code' => $order_wrapper->commerce_order_total->currency_code->value(),
    'data' => array(),
  );
}
