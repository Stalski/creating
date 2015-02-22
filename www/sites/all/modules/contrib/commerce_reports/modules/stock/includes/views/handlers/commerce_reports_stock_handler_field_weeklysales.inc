<?php

/**
 * Stock lifetime
 */
class commerce_reports_stock_handler_field_weeklysales extends views_handler_field_custom {

  function render($values) {
    $sku = $values->commerce_product_sku;
    $new_value = _commerce_reports_stock_calculate_dataset($sku, 'weeklysales');
    if (is_array($new_value)) {
      $new_value = '0.0';
    }

    return $new_value;
  }
}
