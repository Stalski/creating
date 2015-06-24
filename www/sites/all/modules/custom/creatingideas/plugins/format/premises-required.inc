<?php

/**
 * @file
 * The default format for adresses.
 */

$plugin = array(
  'title' => t('Premises required'),
  'format callback' => 'creatingideas_addressfield_format_premises_required',
  'type' => 'address',
  'weight' => -100,
);

/**
 * Format callback.
 *
 * @see CALLBACK_addressfield_format_callback()
 */
function creatingideas_addressfield_format_premises_required(&$format, $address, $context = array()) {
  $format['street_block']['premise']['#required'] = TRUE;
}
