<?php

/**
 * @file
 * Functions for the payment method implementation.
 */



/**
 * Payment method callback: checkout form.
 */
function creatingideas_offsite_submit_form($payment_method, $pane_values, $checkout_pane, $order) {
  //global $language;
  //$session_lang = $language->language;

  $form = array();

  $settings = $payment_method['settings'];

  //$language = $settings['payment_settings_wrapper']["method_0"]['language'][$session_lang];
  //if ($language) {
    $method_message = $settings['payment_settings_wrapper']["method_0"]['details']['value'];
  //}

  //$title = $settings['payment_settings_wrapper']['title'];
  $form['method_options'] = array(
    '#type' => 'markup',
    '#markup' => $method_message,
  );

  return $form;
}

/**
 * Payment method callback: checkout form validation.
 */
function creatingideas_offsite_submit_form_validate($payment_method, $pane_form, $pane_values, $order, $form_parents = array()) {
  if ($pane_form['method_options']['#value'] == 'none') {
    form_set_error('method_options', t('Please select a payment option for the Offsite Payment method.'));
    return FALSE;
  }
}

/**
 * Payment method callback: checkout form submission.
 */
function creatingideas_offsite_submit_form_submit($payment_method, $pane_form, $pane_values, $order, $charge) {
  $choosen_method = $pane_values['method_options'];
  $method_details = array(
    'value' => $pane_form['method_options'][$choosen_method]['#title'],
    'method_number' => $choosen_method,
  );

  // Prepare a transaction object.
  $transaction = commerce_payment_transaction_new('offsite', $order->order_id);
  $transaction->instance_id = $payment_method['instance_id'];
  $transaction->amount = $charge['amount'];
  $transaction->status = COMMERCE_PAYMENT_STATUS_PENDING;

  $transaction->message = t('Choosen method: @method', array('@method' => $choosen_method));

  // Save the transaction.
  commerce_payment_transaction_save($transaction);

  $order->data['creatingideas'] = serialize($method_details);
}


/**
 * Checkout pane callback: Wraps the completion message with a custom div.
 */
function creatingideas_completion_message_pane_checkout_form($form, &$form_state, $checkout_pane, $order) {
  // Build the original message pane.
  $pane_form = commerce_checkout_completion_message_pane_checkout_form($form, $form_state, $checkout_pane, $order);

  if ($order->data['payment_method'] == 'offsite|commerce_payment_offsite') {
    // Add and extra div.
    $pane_form['creatingideas_header'] = array(
      '#markup' => '<div class="commerce-offsite-header">' . creatingideas_make_header($order) . '</div>',
      '#weight' => -10,
    );
  }
  return $pane_form;
}

/**
 * Helper function for building the Payment Details Header.
 *
 * @param Object $order
 *   The Order Object.
 *
 * @return String
 *   The html header.
 */
function creatingideas_make_header($order) {
  $output = unserialize($order->data['creatingideas']);

  return $output['value'];
}

// --------------------

/**
 * Payment method callback: settings form.
 */
function creatingideas_offsite_settings_form($settings = NULL) {
  $languages = array();
  foreach(language_list() as $code => $values) {
    $languages[$code] = $values->name;
  }

  $form = array();

  $form['#tree'] = TRUE;
  $form['payment_settings_wrapper'] = array(
    '#type' => 'markup',
    '#prefix' => '<div id="payment-settings-wrapper">',
    '#suffix' => '</div>',
  );

  if (empty($settings['method_count'])) {
    $settings['method_count'] = 1;
  }

  $form['method_count'] = array(
    '#type' => 'hidden',
    '#value' => $settings['method_count'],
    '#default_value' => $settings['method_count'],
  );

  $form['payment_settings_wrapper']['title'] = array(
    '#type' => 'textfield',
    '#title' => t("Payment Method Title"),
    '#description' => t("This is going to be the method name shown on the checkout payment pane. This value is translatable."),
    '#default_value' => (empty($settings['payment_settings_wrapper']) ? '' : $settings['payment_settings_wrapper']['title']),
    '#required' => TRUE,
  );

  for ($i = 0; $i < $settings['method_count']; $i++) {
    $form['payment_settings_wrapper']["method_$i"] = array(
      '#type' => 'fieldset',
      '#title' => t('Method %count', array('%count' => $i+1)),
      '#collapsible' => TRUE,
    );

    $form['payment_settings_wrapper']["method_$i"]['language'] = array(
      '#type' => 'checkboxes',
      '#title' => t("Language"),
      '#description' => t("This payment details will show up only for the selected language."),
      '#options' => $languages,
      '#default_value' => (empty($settings['payment_settings_wrapper']) ? array() : $settings['payment_settings_wrapper']["method_$i"]['language']),
      '#required' => TRUE,
    );

    $form['payment_settings_wrapper']["method_$i"]['details'] = array(
      '#type'=>'text_format',
      '#title' => t('Payment Details'),
      '#default_value' => (empty($settings['payment_settings_wrapper']) ? array() : $settings['payment_settings_wrapper']["method_$i"]['details']['value']),
      '#format'=>'full_html',
      '#required' => TRUE,
    );
  }
  $form['payment_settings_wrapper']['add_name'] = array(
    '#type' => 'submit',
    '#value' => t('Add another payment details'),
    '#submit' => array('creatingideas_offsite_add_more_add_details'),
    '#ajax' => array(
      'callback' => 'creatingideas_offsite_add_more_callback',
      'wrapper' => 'payment-settings-wrapper',
    ),
  );
  if ($settings['method_count'] > 1) {
    $form['payment_settings_wrapper']['remove_details'] = array(
      '#type' => 'submit',
      '#value' => t('Remove payment details'),
      '#submit' => array('creatingideas_offsite_add_more_remove_details'),
      '#ajax' => array(
        'callback' => 'creatingideas_offsite_add_more_callback',
        'wrapper' => 'payment-settings-wrapper',
      ),
    );
  }

  return $form;
}

/**
 * Callback for both ajax-enabled buttons.
 */
function creatingideas_offsite_add_more_callback($form, $form_state) {
  return $form['parameter']['payment_method']['settings']['payment_method']['settings']['payment_settings_wrapper'];
}

/**
 * Submit handler for the "add-one-more" button.
 *
 * Increments the max counter and causes a rebuild.
 */
function creatingideas_offsite_add_more_add_details($form, &$form_state) {
  $form_state['values']['parameter']['payment_method']['settings']['payment_method']['settings']['method_count']++;
  $form_state['rebuild'] = TRUE;
}

/**
 * Submit handler for the "remove one" button.
 *
 * Decrements the max counter and causes a form rebuild.
 */
function creatingideas_offsite_add_more_remove_details($form, &$form_state) {
  if ($form_state['values']['parameter']['payment_method']['settings']['payment_method']['settings']['method_count'] > 1) {
    $form_state['values']['parameter']['payment_method']['settings']['payment_method']['settings']['method_count']--;
  }
  $form_state['rebuild'] = TRUE;
}