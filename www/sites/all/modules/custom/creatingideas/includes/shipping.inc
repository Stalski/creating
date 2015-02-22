<?php

/**
 * @file
 * Shipping methods and service callbacks.
 */

/**
 * Callback for the Bpost flat rate service.
 */
function creatingideas_rate_bpost($shipping_service, $order) {
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
  return array(
    'amount' => 450,
    'currency_code' => $order_wrapper->commerce_order_total->currency_code->value(),
    'data' => array(),
  );
}

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
