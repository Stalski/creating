<?php

/**
 * @file
 * Handle administration forms for bpost module.
 */

/**
 * Configuration form to store bpost settings.
 */
function commerce_bpost_configure_form($form, &$form_state) {
  $commerce_bpost_settings = variable_get('commerce_bpost_settings', array());
  $form['account'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('Account settings'),
  );
  $form['account']['account_id_help'] = array(
    '#markup' => t('You need a bpost user account to use this module. Call 02/201 11 11 for more information.'),
  );
  $form['account']['account_id'] = array(
    '#type' => 'textfield',
    '#title' => t('API Account id'),
    '#description' => t('Fill in your 6 number account ID - Identifier of the bpost account.'),
    '#default_value' => isset($commerce_bpost_settings['account']['account_id']) ? $commerce_bpost_settings['account']['account_id'] : '',
    '#required' => TRUE,
  );
  $form['account']['passphrase'] = array(
    '#type' => 'textfield',
    '#title' => t('API Passphrase'),
    '#description' => t('Fill in your passphrase that is configured in the bpost Shipping Manager application. Remark: this is not the password to login to bpost.'),
    '#default_value' => isset($commerce_bpost_settings['account']['passphrase']) ? $commerce_bpost_settings['account']['passphrase'] : '',
    '#required' => TRUE,
  );
  $form['account']['api_url'] = array(
    '#type' => 'textfield',
    '#title' => t('API URL'),
    '#default_value' => isset($commerce_bpost_settings['account']['api_url']) ? $commerce_bpost_settings['account']['api_url'] : 'https://api.bpost.be/services/shm/',
    '#required' => TRUE,
  );
  $form['google_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Google map API key'),
    '#description' => t("Using an API key enables you to monitor your application's Maps API usage, and ensures that Google can contact you about your application if necessary. If your application's Maps API usage exceeds the !usage_limits, you must use an API key in order to purchase additional quota.", array('!usage_limits' => l(t('Usage Limits'), 'https://developers.google.com/maps/documentation/javascript/usage#usage_limits'))),
    '#default_value' => isset($commerce_bpost_settings['gmap']['google_api_key']) ? $commerce_bpost_settings['gmap']['google_api_key'] : '',
  );
  $form['gmap'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t("Default values are optimized for checkout process. But you can change them according to your needs."),
    '#title' => t('Google map settings'),
  );
  $form['gmap']['id'] = array(
    '#type' => 'textfield',
    '#title' => t('Map id'),
    '#description' => t('HTML id attribute'),
    '#default_value' => isset($commerce_bpost_settings['gmap']['id']) ? $commerce_bpost_settings['gmap']['id'] : '',
  );
  $form['gmap']['width'] = array(
    '#type' => 'textfield',
    '#title' => t('Map width'),
    '#description' => t('HTML width attribute'),
    '#default_value' => isset($commerce_bpost_settings['gmap']['width']) ? $commerce_bpost_settings['gmap']['width'] : '',
  );
  $form['gmap']['height'] = array(
    '#type' => 'textfield',
    '#title' => t('Map height'),
    '#description' => t('HTML height attribute'),
    '#default_value' => isset($commerce_bpost_settings['gmap']['height']) ? $commerce_bpost_settings['gmap']['height'] : '',
  );
  $form['gmap']['zoom'] = array(
    '#type' => 'textfield',
    '#title' => t('Map zoom'),
    '#description' => t('Define a static zoom value. ( Not used when auto-zoom is enabled )'),
    '#element_validate' => array('element_validate_integer_positive'),
    '#default_value' => isset($commerce_bpost_settings['gmap']['zoom']) ? $commerce_bpost_settings['gmap']['zoom'] : '',
    '#states' => array(
      'disabled' => array(
        ':input[name="gmap[autozoom]"]' => array('value' => 1),
      ),
    ),
  );
  $form['gmap']['autozoom'] = array(
    '#type' => 'radios',
    '#title' => t('Map auto-zoom'),
    '#description' => t('Allow map to get the correct zoom value according to the generated markers.'),
    '#default_value' => isset($commerce_bpost_settings['gmap']['autozoom']) ? $commerce_bpost_settings['gmap']['autozoom'] : '',
    '#options' => array(0 => t('Disable'), 1 => t('Enable')),
  );
  $form['gmap']['street_view_control'] = array(
    '#type' => 'radios',
    '#title' => t('Street view control'),
    '#description' => t('Enable Street View.'),
    '#default_value' => isset($commerce_bpost_settings['gmap']['street_view_control']) ? $commerce_bpost_settings['gmap']['street_view_control'] : '',
    '#options' => array(0 => t('Disable'), 1 => t('Enable')),
  );
  $form['gmap']['map_type_control'] = array(
    '#type' => 'radios',
    '#title' => t('Map controls'),
    '#description' => t('Show map controls.'),
    '#default_value' => isset($commerce_bpost_settings['gmap']['map_type_control']) ? $commerce_bpost_settings['gmap']['map_type_control'] : '',
    '#options' => array(0 => t('Disable'), 1 => t('Enable')),
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  $form += _commerce_bpost_add_help_item();

  return $form;
}

function commerce_bpost_configure_form_validate($form, &$form_state) {
  if (commerce_bpost_webservice_validate_credentials($form_state['values']['account']['account_id'], $form_state['values']['account']['passphrase'], $form_state['values']['account']['api_url'])) {
    drupal_set_message(t('API credentials successfully validated'));
  }
  else {
    form_set_error('bpost_credentials', t('Invalid Shipping Manager Account ID, Passphrase or Api url.'));
  }
}

function commerce_bpost_configure_form_submit($form, &$form_state) {
  $commerce_bpost_settings = variable_get('commerce_bpost_settings', array());
  if (isset($form_state['values']['account']['account_id'])) {
    $commerce_bpost_settings['account']['account_id'] = $form_state['values']['account']['account_id'];
  }
  if (isset($form_state['values']['account']['passphrase'])) {
    $commerce_bpost_settings['account']['passphrase'] = $form_state['values']['account']['passphrase'];
  }
  if (isset($form_state['values']['account']['api_url'])) {
    $commerce_bpost_settings['account']['api_url'] = $form_state['values']['account']['api_url'];
  }
  if (isset($form_state['values']['google_api_key'])) {
    $commerce_bpost_settings['gmap']['google_api_key'] = $form_state['values']['google_api_key'];
  }
  if (isset($form_state['values']['gmap']['id'])) {
    $commerce_bpost_settings['gmap']['id'] = $form_state['values']['gmap']['id'];
  }
  if (isset($form_state['values']['gmap']['width'])) {
    $commerce_bpost_settings['gmap']['width'] = $form_state['values']['gmap']['width'];
  }
  if (isset($form_state['values']['gmap']['height'])) {
    $commerce_bpost_settings['gmap']['height'] = $form_state['values']['gmap']['height'];
  }
  if (isset($form_state['values']['gmap']['zoom'])) {
    $commerce_bpost_settings['gmap']['zoom'] = $form_state['values']['gmap']['zoom'];
  }
  if (isset($form_state['values']['gmap']['autozoom'])) {
    $commerce_bpost_settings['gmap']['autozoom'] = $form_state['values']['gmap']['autozoom'];
  }
  if (isset($form_state['values']['gmap']['street_view_control'])) {
    $commerce_bpost_settings['gmap']['street_view_control'] = $form_state['values']['gmap']['street_view_control'];
  }
  if (isset($form_state['values']['gmap']['map_type_control'])) {
    $commerce_bpost_settings['gmap']['map_type_control'] = $form_state['values']['gmap']['map_type_control'];
  }
  variable_set('commerce_bpost_settings', $commerce_bpost_settings);
  drupal_set_message(t('Configuration saved'));
}

function commerce_bpost_tracking_email_form($form, &$form_state) {
  $commerce_bpost_settings = variable_get('commerce_bpost_settings', array());
  $form['tracking'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('Track & trace'),
  );
  $form['tracking']['track'] = array(
    '#type' => 'radios',
    '#options' => array(
      'auto' => t('T&T email is automatically sent to the customer'),
      'disable' => t('Automatic T&T email is disabled.'),
    ),
    '#default_value' => isset($commerce_bpost_settings['tracking']['track']) ? $commerce_bpost_settings['tracking']['track'] : 'disable',
    '#required' => TRUE,
  );

  $form['email'] = array(
    '#type' => 'fieldset',
    '#title' => t('E-mail'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#tree' => TRUE,
    '#description' => t('Edit the tracking e-mail messages sent to users once the parcel has been sent.') . ' ' . t('Available variables are: [site:name], [site:url], [user:name], [user:mail], [site:login-url], [site:url-brief], [user:edit-url], [commerce-order:order-id], [bpost-tracking-url].'),
  );
  $form['email']['subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Subject'),
    '#default_value' => _commerce_bpost_mail_text('tracking_mail_subject', array(), FALSE),
    '#maxlength' => 180,
  );
  $form['email']['body'] = array(
    '#type' => 'textarea',
    '#title' => t('Body'),
    '#default_value' => _commerce_bpost_mail_text('tracking_mail_body', array(), FALSE),
    '#rows' => 15,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  $form += _commerce_bpost_add_help_item();
  return $form;
}

function commerce_bpost_tracking_email_form_submit($form, &$form_state) {
  $commerce_bpost_settings = variable_get('commerce_bpost_settings', array());
  if (isset($form_state['values']['tracking']['track'])) {
    $commerce_bpost_settings['tracking']['track'] = $form_state['values']['tracking']['track'];
  }
  if (isset($form_state['values']['email']['subject']) && isset($form_state['values']['email']['body'])) {
    $commerce_bpost_settings['tracking']['email']['tracking_mail_subject'] = $form_state['values']['email']['subject'];
    $commerce_bpost_settings['tracking']['email']['tracking_mail_body'] = $form_state['values']['email']['body'];
  }
  variable_set('commerce_bpost_settings', $commerce_bpost_settings);
  drupal_set_message(t('Configuration saved'));
}

/**
 * Configuration form for Labels.
 */
function commerce_bpost_label_form($form, &$form_state) {
  $settings = variable_get('commerce_bpost_settings', array());
  $form['label'] = array(
    '#type' => 'fieldset',
    '#title' => t('Label settings'),
    '#tree' => TRUE,
  );
  $form['label']['method'] = array(
    '#type' => 'radios',
    '#description' => t('Define which system manages the labels'),
    '#options' => array('drupal' => t('Use the Drupal Commerce back office to generate labels (default)'), 'bpost' => t('Use the bpost backoffice to manage labels')),
    '#default_value' => isset($settings['label']['method']) ? $settings['label']['method']: 'drupal',
  );
  $form['label']['format'] = array(
    '#type' => 'fieldset',
    '#title' => t('Formats'),
    '#states' => array(
      'visible' => array(
        ':input[name="label[method]"]' => array('value' => 'drupal'),
      ),
    ),
  );
  $form['label']['format']['settings'] = array(
    '#type' => 'radios',
    '#description' => t('Default format of labels'),
    '#options' => array('A4' => t('Default format A4 (PDF) (Default)'), 'A6' => t('Default format A6 (PDF)')),
    '#default_value' => isset($settings['label']['format']) ? $settings['label']['format']: 'A4',
  );
  $form['label']['return'] = array(
    '#type' => 'fieldset',
    '#title' => t('Retours'),
    '#states' => array(
      'visible' => array(
        ':input[name="label[method]"]' => array('value' => 'drupal'),
      ),
    ),
  );
  $form['label']['return']['settings'] = array(
    '#type' => 'radios',
    '#description' => t('Retour labels'),
    '#options' => array('not_include' => t('Do not include retour label by default (Default value)'), 'include' => t('Always include retour label')),
    '#default_value' => isset($settings['label']['return']) ? $settings['label']['return']: 'not_include',
  );
  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  $form += _commerce_bpost_add_help_item();

  return $form;
}

function commerce_bpost_label_form_submit($form, &$form_state) {
  $settings = variable_get('commerce_bpost_settings', array());
  $settings['label'] = array('method' => $form_state['values']['label']['method'], 'format' => $form_state['values']['label']['format']['settings'], 'return' => $form_state['values']['label']['return']['settings']);
  variable_set('commerce_bpost_settings', $settings);
  drupal_set_message(t('Configuration saved'));
}

/**
 * Configuration form for Shipping services.
 */
function commerce_bpost_shipping_services_form($form, &$form_state) {
  $settings = variable_get('commerce_bpost_settings', array());
  include_once DRUPAL_ROOT . '/includes/locale.inc';
  $country_list = country_get_list();

  $selected_countries = array();
  if (isset($form_state['values']['shipping_services']['countries_list_enabled'])) {
    $selected_countries = $form_state['values']['shipping_services']['countries_list_enabled'];
  }
  elseif (isset($settings['shipping_services']['country_list'])) {
    $selected_countries = array_intersect_key($country_list, $settings['shipping_services']['country_list']);
  }

  // Attach assets.
  $form['#attached']['js'] = array(
    drupal_get_path('module', 'commerce_bpost') . '/theme/js/multiselect-list.js',
    array(
      'data' => array('commercebpost_country_list' => $selected_countries),
      'type' => 'setting'
    ),
  );
  $form['#attached']['css'] = array(
    drupal_get_path('module', 'commerce_bpost') . '/theme/css/shipping_services.css'
  );
  $form['help_message'] = array(
    '#prefix' => '<div class="messages warning">',
    '#markup' => t('The selected countries also have to be enabled in your bpost Shipping Manager. Click this <a href="@link">link</a> for more information.',
      array('@link' => 'http://bpost.freshdesk.com/support/solutions/articles/74703-error-1320-customer')),
    '#suffix' => '</div>',
  );
  $form['shipping_services'] = array(
    '#type' => 'fieldset',
    '#title' => t('Country settings'),
    '#tree' => TRUE,
  );

  // Multiselect list
  // Allow user to enable options by moving them from left to right list.
  $country_list = array_intersect_key($country_list, commerce_bpost_get_countries_from_shipping_manager());
  $form['shipping_services']['countries_list_available'] = array(
    '#type' => 'select',
    '#description' => t('Choose countries for which bpost needs to be enabled'),
    '#options' => $country_list,
    '#multiple' => TRUE,
    '#size' => 20,
    '#prefix' => '<div id="countries-list-available">',
    '#suffix' => '</div>',
  );
  $form['shipping_services']['add'] = array(
    '#type' => 'button',
    '#value' => '>',
    '#prefix' => '<div id="multiselect-list-actions-wrapper"><div id="multiselect-list-actions">',
  );
  $form['shipping_services']['remove'] = array(
    '#type' => 'button',
    '#value' => '<',
    '#suffix' => '</div></div>',
  );
  $form['shipping_services']['countries_list_enabled'] = array(
    '#type' => 'select',
    '#description' => t('Countries enabled for bpost'),
    '#options' => $country_list,
    '#multiple' => TRUE,
    '#size' => 20,
  );
  $form['refresh'] = array(
    '#type' => 'submit',
    '#value' => t('Refresh'),
  );
  $form['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  $form += _commerce_bpost_add_help_item();

  return $form;
}

function commerce_bpost_shipping_services_form_submit($form, &$form_state) {
  if ($form_state['values']['op'] == 'Refresh') {
    cache_clear_all('commerce_bpost_shopinfo', 'cache');
    drupal_set_message(t('Countries refreshed from bpost shipping manager'));
  }
  elseif ($form_state['values']['op'] == 'Save') {
    // Update shipping services settings.
    $settings = variable_get('commerce_bpost_settings', array());
    $countries_list_enabled = $form_state['values']['shipping_services']['countries_list_enabled'];
    $settings['shipping_services'] = array(
      'country_list' => $countries_list_enabled,
    );
    variable_set('commerce_bpost_settings', $settings);
    drupal_set_message(t('Configuration saved'));
  }
}

function theme_commerce_bpost_mapping_form($variables) {
  $form = array();
  $form['statuses'] = array('#markup' => drupal_render($variables['form']['statuses']));
  $form['shipping'] = array('#markup' => drupal_render($variables['form']['shipping']));
  if (!empty($variables['form']['profile']['fields'])) {
    $variables['form']['profile']['fields'] = array(
      '#markup' => theme('commerce_bpost_profile_mapping', array(
          'form_element_mapping' => $variables['form']['profile']['fields'],
          'attributes' => array('id' => array('bpost-profile-mapping')),
        )
      )
    );
  }
  if (!empty($variables['form']['order']['fields'])) {
    $variables['form']['order']['fields'] = array(
      '#markup' => theme('commerce_bpost_order_mapping', array(
          'form_element_mapping' => $variables['form']['order']['fields'],
        )
      )
    );
  }
  return drupal_render($form) . drupal_render_children($variables['form']);
}

/**
 * Configure order.
 */
function commerce_bpost_mapping_form($form, &$form_state) {
  $form = array();
  $commerce_bpost_settings = variable_get('commerce_bpost_settings', array());
  // Sender.
  $form['sender'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('Sender'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  foreach ($commerce_bpost_settings['bpost_fields']['sender'] as $field_sender_name => $field_sender_info) {
    $form['sender'][$field_sender_name] = array(
      '#type' => 'textfield',
      '#title' => check_plain($field_sender_info['title']),
      '#required' => $field_sender_info['required'],
      '#description' => filter_xss($field_sender_info['description']),
      '#default_value' => isset($commerce_bpost_settings['mapping']['sender'][$field_sender_name]) ? $commerce_bpost_settings['mapping']['sender'][$field_sender_name]: NULL,
    );
  }
  // Order status.
  $form['statuses'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('Order status'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $commerce_order_status_options = commerce_order_status_options_list();
  $commerce_order_states_options = commerce_order_state_options_list();
  if (!empty($commerce_bpost_settings['mapping']['validation_status'])) {
    $default = $commerce_bpost_settings['mapping']['validation_status'];
  }
  else {
    $default = 'completed';
  }
  $form['statuses']['status'] = array(
    '#type' => 'select',
    '#title' => t('Select the order status in order to send the order directly to Bpack.'),
    '#options' => $commerce_order_status_options,
    '#description' => t('Match the Drupal order status which validates the order sending.'),
    '#default_value' => $default,
  );
  if (!empty($commerce_bpost_settings['mapping']['canceling_status'])) {
    $default = $commerce_bpost_settings['mapping']['canceling_status'];
  }
  else {
    $default = 'canceled';
  }
  $form['statuses']['cancel'] = array(
    '#type' => 'select',
    '#title' => t('Select the order status where the order should be sent to bpost as canceled.'),
    '#options' => $commerce_order_status_options,
    '#description' => t('Match the Drupal order status which canceling the order.'),
    '#default_value' => $default,
  );
  // Shipping status.
  $form['shipping'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('Shipping status'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  $form['shipping']['open_status'] = array(
    '#type' => 'select',
    '#multiple' => TRUE,
    '#required' => TRUE,
    '#title' => t('Open'),
    '#options' => $commerce_order_states_options,
    '#description' => t('Match the Drupal order status which is the open status.'),
    '#default_value' => isset($commerce_bpost_settings['mapping']['open_status']) ? $commerce_bpost_settings['mapping']['open_status']: 'completed',
  );
  $form['shipping']['treated_status'] = array(
    '#type' => 'select',
    '#multiple' => TRUE,
    '#required' => TRUE,
    '#title' => t('Treated'),
    '#options' => $commerce_order_states_options,
    '#description' => t('Match the Drupal order status which is the treated status.'),
    '#default_value' => isset($commerce_bpost_settings['mapping']['treated_status']) ? $commerce_bpost_settings['mapping']['treated_status']: 'completed',
  );
  // Profil Mapping.
  $form['profile'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('Profile mapping'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#prefix' => '<div id="bpost-profile-mapping">',
    '#suffix' => '</div>',
  );
  $form['profile']['customer_profile'] = array(
    '#type' => 'select',
    '#title' => t('Customer profile to use'),
    '#required' => TRUE,
    '#options' => array('' => t('Select a customer profile')) + commerce_customer_profile_type_options_list(),
    '#description' => t("Which customer profile store the shipping address of your customer? Box and number field are really needed by the Bpost Web-service, if not mapped the address sent to bpost won't be valid"),
    '#ajax' => array(
      'callback' => 'commerce_bpost_ajax_get_profile_fields',
      'wrapper' => 'bpost-profile-mapping',
    ),
    '#default_value' => !empty($commerce_bpost_settings['mapping']['customer_profile']) ? $commerce_bpost_settings['mapping']['customer_profile'] : '',
  );
  if (!empty($form_state['values']['profile']['customer_profile'])) {
    $customer_profile_type = $form_state['values']['profile']['customer_profile'];
  }
  elseif (!empty($commerce_bpost_settings['mapping']['customer_profile'])) {
    $customer_profile_type = $commerce_bpost_settings['mapping']['customer_profile'];
  }
  if (!empty($customer_profile_type)) {
    foreach ($commerce_bpost_settings['bpost_fields']['receiver'] as $field_name => $info) {
      $form['profile']['fields'][$field_name] = array(
        '#title' => check_plain(t($field_name)),
        '#type' => 'select',
        '#options' => array('' => '- empty -') + array_merge(commerce_bpost_get_all_customer_profile_fields($customer_profile_type), commerce_bpost_get_all_user_fields()),
        '#description' => filter_xss($info['description']),
        '#required' => $info['required'],
        '#default_value' => !empty($commerce_bpost_settings['mapping']['profile']['fields'][$field_name]) ? $commerce_bpost_settings['mapping']['profile']['fields'][$field_name] : '',
      );
    }
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  $form += _commerce_bpost_add_help_item();
  return $form;
}

function commerce_bpost_mapping_form_submit($form, &$form_state) {
  $commerce_bpost_settings = variable_get('commerce_bpost_settings', array());
  if (isset($form_state['values']['statuses']['status'])) {
    $commerce_bpost_settings['mapping']['validation_status'] = $form_state['values']['statuses']['status'];
  }
  if (isset($form_state['values']['statuses']['cancel'])) {
    $commerce_bpost_settings['mapping']['canceling_status'] = $form_state['values']['statuses']['cancel'];
  }
  if (isset($form_state['values']['shipping']['treated_status'])) {
    $commerce_bpost_settings['mapping']['treated_status'] = $form_state['values']['shipping']['treated_status'];
  }
  if (isset($form_state['values']['shipping']['open_status'])) {
    $commerce_bpost_settings['mapping']['open_status'] = $form_state['values']['shipping']['open_status'];
  }
  if (isset($form_state['values']['profile']['customer_profile'])) {
    $commerce_bpost_settings['mapping']['customer_profile'] = $form_state['values']['profile']['customer_profile'];
  }
  if (isset($form_state['values']['profile']['fields'])) {
    $commerce_bpost_settings['mapping']['profile']['fields'] = $form_state['values']['profile']['fields'];
  }
  if (isset($form_state['values']['sender']['name'])) {
    $commerce_bpost_settings['mapping']['sender']['name'] = $form_state['values']['sender']['name'];
  }
  if (isset($form_state['values']['sender']['company'])) {
    $commerce_bpost_settings['mapping']['sender']['company'] = $form_state['values']['sender']['company'];
  }
  if (isset($form_state['values']['sender']['streetName'])) {
    $commerce_bpost_settings['mapping']['sender']['streetName'] = $form_state['values']['sender']['streetName'];
  }
  if (isset($form_state['values']['sender']['number'])) {
    $commerce_bpost_settings['mapping']['sender']['number'] = $form_state['values']['sender']['number'];
  }
  if (isset($form_state['values']['sender']['box'])) {
    $commerce_bpost_settings['mapping']['sender']['box'] = $form_state['values']['sender']['box'];
  }
  if (isset($form_state['values']['sender']['postalCode'])) {
    $commerce_bpost_settings['mapping']['sender']['postalCode'] = $form_state['values']['sender']['postalCode'];
  }
  if (isset($form_state['values']['sender']['locality'])) {
    $commerce_bpost_settings['mapping']['sender']['locality'] = $form_state['values']['sender']['locality'];
  }
  if (isset($form_state['values']['sender']['mail'])) {
    $commerce_bpost_settings['mapping']['sender']['mail'] = $form_state['values']['sender']['mail'];
  }
  if (isset($form_state['values']['sender']['phoneNumber'])) {
    $commerce_bpost_settings['mapping']['sender']['phoneNumber'] = $form_state['values']['sender']['phoneNumber'];
  }
  cache_clear_all('ctools_export:views_view:commerce_backoffice_orders', "cache_views");
  variable_set('commerce_bpost_settings', $commerce_bpost_settings);
  drupal_set_message(t('Configuration saved'));
}



/**
 * Ajax callback to get customer profile type fields
 */
function commerce_bpost_ajax_get_profile_fields($form, $form_state) {
  if (!empty($form_state['values']['profile']['customer_profile'])) {
    $form['profile']['fields'] = array(
      '#markup' => theme('commerce_bpost_profile_mapping', array(
          'form_element_mapping' => $form['profile']['fields'],
          'attributes' => array('id' => array('bpost-profile-mapping')),
        )
      )
    );
  }
  else {
    unset($form['profile']['fields']);
  }

  return $form['profile'];
}

/**
 * Configure bpost product options.
 */
function commerce_bpost_options_form($form, &$form_state) {
  $form = array();
  $commerce_bpost_settings = variable_get('commerce_bpost_settings', array());

  // delivery options
  $form['delivery_options'] = array(
      '#tree' => TRUE,
      '#type' => 'fieldset',
      '#title' => t('Delivery options'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
  // Home delivery.
  $form['delivery_options']['bpost_home'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Home delivery'),
    '#options' => array(
      'second_presentation' => t('2nd Presentation'),
      'insurance' => t('Insurance'),
      'signature' => t('Signature'),
    ),
    '#default_value' => !empty($commerce_bpost_settings['options']['bpost_home']) ? $commerce_bpost_settings['options']['bpost_home'] : array(),
    '#description' => t('<b>2nd Presentation</b>: This options provides automatically a second presentation at the receiver\'s address should he be absent upon first presentation.</br><b>Insurance</b>: Insurance to insure your goods to a maximum of 500,00 euros.</br><b>Signature</b>: The delivery happens against signature by the receiver.'),
  );
  // Pick-up point.
  $form['delivery_options']['bpost_postoffice_postpoint'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Pick-up point'),
    '#options' => array(
      'insurance' => t('Insurance'),
    ),
    '#default_value' => !empty($commerce_bpost_settings['options']['bpost_postoffice_postpoint']) ? $commerce_bpost_settings['options']['bpost_postoffice_postpoint'] : array(),
    '#description' => t('<b>Insurance</b>: Insurance to insure your goods to a maximum of 500,00 euros.'),
  );
  // Parcel locker.
  $form['delivery_options']['bpost_bpack'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Parcel locker'),
    '#options' => array(
      'insurance' => t('Insurance'),
    ),
    '#default_value' => !empty($commerce_bpost_settings['options']['bpost_bpack']) ? $commerce_bpost_settings['options']['bpost_bpack'] : array(),
    '#description' => t('<b>Insurance</b>: Insurance to insure your goods to a maximum of 500,00 euros.'),
  );
  // World.
  $form['delivery_options']['bpost_world'] = array(
    '#type' => 'checkboxes',
    '#title' => t('World'),
    '#options' => array(
      'insurance_basic' => t('Insurance basic'),
    ),
    '#default_value' => !empty($commerce_bpost_settings['options']['bpost_world']) ? $commerce_bpost_settings['options']['bpost_world'] : array(),
    '#description' => t('<b>Insurance basic</b>: Insurance to insure your goods to a maximum of 500,00 euros.'),
  );

  // Delivery settings
  $form['delivery_settings'] = array(
    '#tree' => TRUE,
    '#type' => 'fieldset',
    '#title' => t('Delivery settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['delivery_settings']['international_delivery'] = array(
    '#type' => 'radios',
    '#title' => t('International delivery'),
    '#options' => array(
      'bpack World Business' => t('World Business'),
      'bpack World Express Pro' => t('World Express Pro'),
    ),
    '#default_value' => !empty($commerce_bpost_settings['options']['international_delivery']) ? $commerce_bpost_settings['options']['international_delivery'] : 'bpack World Business',
    '#description' => t('Choose international delivery options'),
  );

  $form['#attached']['js'][] = array(
    'data' => drupal_get_path('module', 'commerce_bpost') . '/theme/js/commerce_bpost_option.js',
    'type' => 'file',
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  $form += _commerce_bpost_add_help_item();
  return $form;
}

function commerce_bpost_options_form_submit($form, &$form_state) {
  $commerce_bpost_settings = variable_get('commerce_bpost_settings', array());

  // Delivery Options.
  $commerce_bpost_settings['options']['bpost_home'] = $form_state['values']['delivery_options']['bpost_home'];
  $commerce_bpost_settings['options']['bpost_postoffice_postpoint'] = $form_state['values']['delivery_options']['bpost_postoffice_postpoint'];
  $commerce_bpost_settings['options']['bpost_bpack'] = $form_state['values']['delivery_options']['bpost_bpack'];
  $commerce_bpost_settings['options']['bpost_world'] = $form_state['values']['delivery_options']['bpost_world'];

  // Delivery Settings.
  $commerce_bpost_settings['options']['international_delivery'] = $form_state['values']['delivery_settings']['international_delivery'];

  variable_set('commerce_bpost_settings', $commerce_bpost_settings);
  drupal_set_message(t('Configuration saved'));
}


/**
 * Retrieve country list from bpost shipping manager.
 */
function commerce_bpost_get_countries_from_shipping_manager() {
  $data = commerce_bpost_get_shop_info();
  $coutry_list = array();
  foreach ($data->deliveryMethod as $deliveryMethod) {
    foreach ($deliveryMethod->product as $product) {
      foreach ($product->price as $price) {
        foreach ($price->attributes() as $key => $value) {
          if ($key == 'countryIso2Code') {
            $coutry_list[(string) $value] = (string) $value;
          }
        }
      }
    }
  }
  return $coutry_list;
}

function _commerce_bpost_add_help_item() {

  $form['more_help'] = array(
    '#type' => 'container',
    '#weight' => 100,
  );
  $form['more_help']['link'] = array(
    '#markup' => l(t('Click here for more information'), 'http://bpost.freshdesk.com/support/solutions/folders/262627', array('absolute' => TRUE, 'attributes' => array('target' => '_blank'))),
  );

  return $form;
}