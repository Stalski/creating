<?php

/**
 * @file
 * All relatives commerce methods for commerce_bpost module.
 */

/**
 * Implements hook_commerce_shipping_method_info().
 */
function commerce_bpost_commerce_shipping_method_info() {
  $shipping_methods = array();

  $shipping_methods['bpost'] = array(
    'title' => t('bpost'),
    'display_title' => t('bpost'),
    'description' => t('Defines a shipping method that handles Belgium shipping services.'),
  );

  return $shipping_methods;
}

/**
 * Implements hook_commerce_shipping_service_info().
 */
function commerce_bpost_commerce_shipping_service_info() {
  $commerce_bpost_settings = variable_get('commerce_bpost_settings', array());
  if (isset($commerce_bpost_settings['options']['international_delivery'])) {
    switch ($commerce_bpost_settings['options']['international_delivery']) {
      case 'bpack World Express Pro':
        $world_name = 'BPACK World Express';
        break;
      default:
        $world_name = 'BPACK World Business';
        break;
    }
  }
  else {
    $world_name = 'BPACK World Business';
  }
  $shipping_services['bpost_home'] = array(
    'title' => t('Home delivery'),
    'description' => t('Your parcel is delivered to the address of your choice (home or work).'),
    'display_title' => t('Home delivery'),
    'shipping_method' => 'bpost',
    'price_component' => 'shipping',
    'callbacks' => array(
      'rate' => 'commerce_bpost_belgian_service_rate',
      'details_form' => 'commerce_bpost_service_details_form',
      'details_form_validate' => 'commerce_bpost_service_details_form_validate',
      'details_form_submit' => 'commerce_bpost_service_details_form_submit',
    ),
  );

  $shipping_services['bpost_postoffice_postpoint'] = array(
    'title' => t('Pick-up point'),
    'description' => t('Your parcel is delivered to a post office or a Post Point. You can choose from more than 1.250 bpost pick-up points.'),
    'display_title' => t('Pick-up point'),
    'shipping_method' => 'bpost',
    'price_component' => 'shipping',
    'callbacks' => array(
      'rate' => 'commerce_bpost_belgian_service_rate',
      'details_form' => 'commerce_bpost_service_details_map_form',
      'details_form_validate' => 'commerce_bpost_service_details_map_postpoint_form_validate',
      'details_form_submit' => 'commerce_bpost_service_details_map_form_submit',
    ),
  );

  $shipping_services['bpost_bpack'] = array(
    'title' => t('Parcel locker'),
    'description' => t('Your parcel is delivered to a bpost parcel locker. These lockers are open 24/7.'),
    'display_title' => t('Parcel locker'),
    'shipping_method' => 'bpost',
    'price_component' => 'shipping',
    'callbacks' => array(
      'rate' => 'commerce_bpost_belgian_service_rate',
      'details_form' => 'commerce_bpost_service_details_map_bpack_form',
      'details_form_validate' => 'commerce_bpost_service_details_map_bpack_form_validate',
      'details_form_submit' => 'commerce_bpost_service_details_map_form_submit',
    ),
  );

  $shipping_services['bpost_world'] = array(
    'title' => t('World'),
    'description' => t('Delivery at your invoice address.'),
    'display_title' => t('@name', array('@name' => $world_name)),
    'shipping_method' => 'bpost',
    'price_component' => 'shipping',
    'callbacks' => array(
      'rate' => 'commerce_bpost_world_service_rate',
      'details_form' => 'commerce_bpost_service_details_form',
      'details_form_validate' => 'commerce_bpost_service_details_form_validate',
      'details_form_submit' => 'commerce_bpost_service_details_form_submit',
    ),
  );

  return $shipping_services;
}

/**
 * Shipping service rate callback.
 */
function commerce_bpost_default_service_rate($shipping_service, $order) {
  // Get customer shipping address country.
  $wrapper_order = entity_metadata_wrapper('commerce_order', $order);
  $country_code = $wrapper_order->commerce_customer_shipping->commerce_customer_address->country->value();

  // Check shipping is enabled for this country.
  // Service is not available if country is disabled.
  $bpost_settings = variable_get('commerce_bpost_settings', array());
  if (isset($bpost_settings['shipping_services']) && !isset($bpost_settings['shipping_services']['country_list'][$country_code])) {
    return FALSE;
  }


  // Get order's weight.
  $weight = commerce_physical_order_weight($order, 'kg');

  // Load rate according to the shipping service and order's weight.
  $rate = commerce_bpost_get_rate_by_weight($shipping_service['name'], $weight);
  $wrapper_rate = entity_metadata_wrapper('commerce_bpost_rate', $rate);
  $rates = $wrapper_rate->rates->value();

  // Return country specific rate's price.
  return isset($rates[$country_code]) ? array('amount' => $rates[$country_code] * 100, 'currency_code' => 'EUR'): FALSE;
}

/**
 * Shipping service rate callback for non Belgium.
 */
function commerce_bpost_belgian_service_rate($shipping_service, $order) {
  if (variable_get('commerce_bpost_credentials', FALSE)) {
    // Shipping services are only available for Belgium.
    $wrapper_order = entity_metadata_wrapper('commerce_order', $order);
    $country_code = $wrapper_order->commerce_customer_shipping->commerce_customer_address->country->value();
    if ($country_code == 'BE') {
      return commerce_bpost_default_service_rate($shipping_service, $order);
    }
  }

  return FALSE;
}

/**
 * Shipping service rate callback for Belgium.
 */
function commerce_bpost_world_service_rate($shipping_service, $order) {
  if (variable_get('commerce_bpost_credentials', FALSE)) {
    // Shipping services are only available outside Belgium.
    $wrapper_order = entity_metadata_wrapper('commerce_order', $order);
    $country_code = $wrapper_order->commerce_customer_shipping->commerce_customer_address->country->value();
    if ($country_code != 'BE') {
      return commerce_bpost_default_service_rate($shipping_service, $order);
    }
  }

  return FALSE;
}

/**
 * Shipping service basic form callback.
 *
 * Checkout pane callback: customer profile edit form.
 * Ensure we have address number and name in separate fields.
 * Either try to automatically split those values or ask user to correct his/her
 * shipping address.
 */
function commerce_bpost_service_details_form($pane_form, $pane_values, $checkout_pane, $order, $shipping_service) {

  // Address
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
  $address = $order_wrapper->commerce_customer_shipping->commerce_customer_address->value();

  $form = array();
  $modification_required = 0;
  if (empty($address['name_line']) or
      empty($address['thoroughfare']) or
      empty($address['postal_code']) or
      empty($address['locality']) or
      empty($address['country'])) {
    // We are missing at least one field, ask user to complete his/her
    // shipping address.
    $modification_required = 1;
  }
  elseif (empty($address['premise'])) {
    $modification_required = 1;
  }

  if ($modification_required) {
    // Get current shipping profile
    $profile = NULL;
    if (isset($order_wrapper->commerce_customer_shipping)) {
      $profile = $order_wrapper->commerce_customer_shipping->value();
    }
    // Create a new shipping profile if it hasn't already been made.
    if (empty($profile)) {
      $profile = commerce_customer_profile_new('shipping', $order->uid);
    }

    // Add the entity context of the current cart order.
    $profile->entity_context = array(
      'entity_type' => 'commerce_order',
      'entity_id' => $order->order_id,
    );

    $form['customer_profile'] = array(
      '#type' => 'value',
      '#value' => $profile,
    );


    // Build form_state since callback call doesn't give us the information.
    $form_state = form_state_defaults();
    $form_state['build_info']['form_id'] = 'commerce_bpost_service_details_form';
    $form_state['values'] = $pane_values;

    // Add the field widgets for the profile.
    field_attach_form('commerce_customer_profile', $profile, $form, $form_state);
    unset($form['#parents']);
    $form['commerce_customer_address'][LANGUAGE_NONE][0]['street_block']['thoroughfare']['#title'] = t('Street name');
    $form['commerce_customer_address'][LANGUAGE_NONE][0]['street_block']['premise']['#title'] = t('Street number');
    $form['commerce_customer_address'][LANGUAGE_NONE][0]['street_block']['premise']['#required'] = TRUE;

    if ($modification_required == 2) {
      // Hide this form, new values will be save but nothing is displayed.
      $form['commerce_customer_address']['#access'] = FALSE;
    }
  }

  return $form;
}

/**
 * Shipping service basic form validate.
 *
 * Checkout pane callback: validate customer profile.
 */
function commerce_bpost_service_details_form_validate($details_form, $details_values, $shipping_service, $order, $form_parents) {

  if (isset($details_values['customer_profile'])) {
    $profile = $details_values['customer_profile'];
    $form_state = array('values' => $details_values);
    // Notify field widgets to validate their data.
    field_attach_form_validate('commerce_customer_profile', $profile, $details_form, $form_state);
  }

  return TRUE;
}

/**
 * Shipping service basic form submit.
 *
 * Checkout pane callback: save customer profile.
 */
function commerce_bpost_service_details_form_submit($details_form, $details_values, $line_item) {

  if (isset($details_values['customer_profile'])) {
    $line_item_wrapper = entity_metadata_wrapper('commerce_line_item', $line_item);
    $order_wrapper = &$line_item_wrapper->order;

    _commerce_bpost_service_customer_profile_save($details_form, $details_values, $order_wrapper);
  }
}

function _commerce_bpost_service_customer_profile_save($details_form, $details_values, $order_wrapper) {
  // Ensure the profile is active.
  $profile = $details_values['customer_profile'];
  $profile->commerce_customer_address = $details_values['commerce_customer_address'];
  $profile->status = TRUE;

  // Set the profile's uid if it's being created at this time.
  if (empty($profile->profile_id)) {
    $profile->uid = $order_wrapper->uid->value();
  }

  // Notify field widgets.
  $form_state = array('values' => $details_values);
  field_attach_submit('commerce_customer_profile', $profile, $details_form, $form_state);

  // Save the profile.
  commerce_customer_profile_save($profile);

  // Store the profile ID for the related field as specified on the settings form.
  $order_wrapper->commerce_customer_shipping = $profile;
}

/**
 * Shipping service bpack form callback.
 *
 * Checkout pane callback: bpack point selection.
 */
function commerce_bpost_service_details_map_bpack_form($pane_form, $pane_values, $checkout_pane, $order, $shipping_service) {
  $commerce_bpost_settings = variable_get('commerce_bpost_settings', array());
  if (commerce_bpost_check_minimal_config_requirement($commerce_bpost_settings)) {

    if ($form = commerce_bpost_service_details_form($pane_form, $pane_values, $checkout_pane, $order, $shipping_service)) {
      return $form;
    }

    $form = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('bpost-shipping-services'),
        'id' => array('delivery-parcel-automate')
      ),
    );

    // Allow user to use another bpack rc code. No really good to use $_REQUEST
    // but there is really nothing to hack there.
    if (isset($_REQUEST['_triggering_element_name']) && $_REQUEST['_triggering_element_name'] == 'op' && isset($_REQUEST['_triggering_element_value']) && $_REQUEST['_triggering_element_value'] == t('Change bpack RC code')) {
      unset($order->data['commerce_bpost']['bpack_member']);
      commerce_order_save($order);
    }

    // Address
    $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
    $commerce_customer_address = $order_wrapper->commerce_customer_shipping->commerce_customer_address;

    // We need a bpack rc code
    if (empty($order->data['commerce_bpost']['bpack_member'])) {
      $form['bpack_account'] = array(
        '#type' => 'fieldset',
        '#title' => t('Select or create a parcel locker account:'),
        '#weight' => 5,
        '#collapsible' => FALSE,
        '#collapsed' => FALSE,
        '#attributes' => array('id' => array('bpost-shipping-map')),
      );
      $form['bpack_account']['account'] = array(
        '#type' => 'radios',
        '#options' => array(
          'new' => t('I would like to register for parcel locker'),
          'registered' => t('I am a parcel locker registered user'),
        ),
        '#element_validate' => array('_commerce_bpost_pane_value_hack'),
      );

      // Bpack check user.
      $form['bpack_account']['member'] = array(
        '#type' => 'container',
        '#attached' => array(
          'css' => array(drupal_get_path('module', 'commerce_bpost') . '/theme/css/overlaypopup.css'),
          'js' => array(drupal_get_path('module', 'commerce_bpost') . '/theme/js/overlaypopup.js'),
        ),
      );
      $form['bpack_account']['member']['rc'] = array(
        '#type' => 'textfield',
        '#title' => t('RC'),
        '#states' => array(
          'visible' => array(
            ':input[name="commerce_shipping[service_details][bpack_account][account]"]' => array('value' => 'registered'),
          ),
        ),
        '#size' => 30,
        '#prefix' => '<div class="container-inline">',
        '#suffix' => '</div>',
        '#element_validate' => array('_commerce_bpost_pane_value_hack'),
      );
      $form['bpack_account']['member']['help'] = array(
        '#markup' => l(t('Where can I find this info?'), '', array('attributes' => array('class' => array('show-popup')), 'fragment' => '', 'html' => TRUE, 'external' => TRUE)),
      );
      $language = commerce_bpost_get_current_language();
      switch ($language) {
        case 'FR':
          $image_help_path = 'bpack_help_fr.png';
          break;
        case 'NL':
          $image_help_path = 'bpack_help.png';
          break;
        default:
          $image_help_path = 'bpack_help_en.png';
            break;
      }

      $form['bpack_account']['member']['help_image'] = array(
        '#markup' => '<div class="overlay"><div class="overlay-content">' .
          theme_image(array(
            'path' => base_path() . drupal_get_path('module', 'commerce_bpost') . '/theme/images/' . $image_help_path,
            'attributes' => array('id' => array('bpack_help_image')),
            'alt' => t('Where to find rc id'),
            'title' => t('Where to find rc id'),
          )) . '<span class="close-btn">Close</span></div></div>',
      );

      // Bpack create member
      $form['bpack_account']['createmember'] = array(
        '#type' => 'container',
        '#attributes' => array('id' => array('bpost-create-member')),
        '#states' => array(
          'visible' => array(
            ':input[name="commerce_shipping[service_details][bpack_account][account]"]' => array('value' => 'new'),
          ),
        ),
        '#tree' => TRUE,
      );
      $form['bpack_account']['createmember']['title'] = array(
        '#type' => 'select',
        '#title' => t('Title'),
        '#options' => array(
          'mr' => t('Mr.'),
          'ms' => t('Ms.'),
        ),
        '#default_value' => '',
        '#states' => array(
          'visible' => array(
            ':input[name="commerce_shipping[service_details][bpack_account][account]"]' => array('value' => 'new'),
          ),
        ),
        '#element_validate' => array('_commerce_bpost_pane_value_hack'),
      );
      $form['bpack_account']['createmember']['firstname'] = array(
        '#type' => 'textfield',
        '#title' => t('Firstname'),
        '#default_value' => $commerce_customer_address->first_name->value(),
        '#states' => array(
          'visible' => array(
            ':input[name="commerce_shipping[service_details][bpack_account][account]"]' => array('value' => 'new'),
          ),
        ),
        '#element_validate' => array('_commerce_bpost_pane_value_hack'),
      );
      $form['bpack_account']['createmember']['lastname'] = array(
        '#type' => 'textfield',
        '#title' => t('Lastname'),
        '#default_value' => $commerce_customer_address->last_name->value(),
        '#states' => array(
          'visible' => array(
            ':input[name="commerce_shipping[service_details][bpack_account][account]"]' => array('value' => 'new'),
          ),
        ),
        '#element_validate' => array('_commerce_bpost_pane_value_hack'),
      );
      $form['bpack_account']['createmember']['email'] = array(
        '#type' => 'textfield',
        '#title' => t('Email'),
        '#default_value' => $order_wrapper->commerce_customer_shipping->user->mail->value(),
        '#states' => array(
          'visible' => array(
            ':input[name="commerce_shipping[service_details][bpack_account][account]"]' => array('value' => 'new'),
          ),
        ),
        '#element_validate' => array('_commerce_bpost_pane_value_hack'),
      );
      $form['bpack_account']['createmember']['street'] = array(
        '#type' => 'textfield',
        '#title' => t('Street'),
        '#default_value' => $commerce_customer_address->thoroughfare->value(),
        '#states' => array(
          'visible' => array(
            ':input[name="commerce_shipping[service_details][bpack_account][account]"]' => array('value' => 'new'),
          ),
        ),
        '#element_validate' => array('_commerce_bpost_pane_value_hack'),
      );
      $form['bpack_account']['createmember']['number'] = array(
        '#type' => 'textfield',
        '#title' => t('Number'),
        '#default_value' => $commerce_customer_address->premise->value(),
        '#states' => array(
          'visible' => array(
            ':input[name="commerce_shipping[service_details][bpack_account][account]"]' => array('value' => 'new'),
          ),
        ),
        '#element_validate' => array('_commerce_bpost_pane_value_hack'),
      );
      $form['bpack_account']['createmember']['city'] = array(
        '#type' => 'textfield',
        '#title' => t('City'),
        '#default_value' => $commerce_customer_address->locality->value(),
        '#states' => array(
          'visible' => array(
            ':input[name="commerce_shipping[service_details][bpack_account][account]"]' => array('value' => 'new'),
          ),
        ),
        '#element_validate' => array('_commerce_bpost_pane_value_hack'),
      );
      $form['bpack_account']['createmember']['postalcode'] = array(
        '#type' => 'textfield',
        '#title' => t('Postal code'),
        '#default_value' => $commerce_customer_address->postal_code->value(),
        '#states' => array(
          'visible' => array(
            ':input[name="commerce_shipping[service_details][bpack_account][account]"]' => array('value' => 'new'),
          ),
        ),
        '#element_validate' => array('_commerce_bpost_pane_value_hack'),
      );
      $form['bpack_account']['createmember']['birth_date'] = array(
        '#type' => 'textfield',
        '#title' => t('Birth date'),
        '#description' => t('Expected format: dd/mm/yyyy'),
        '#default_value' => '',
        '#states' => array(
          'visible' => array(
            ':input[name="commerce_shipping[service_details][bpack_account][account]"]' => array('value' => 'new'),
          ),
        ),
        '#element_validate' => array('_commerce_bpost_pane_value_hack'),
      );
      $form['bpack_account']['createmember']['mobileprefix'] = array(
        '#type' => 'textfield',
        '#title' => t('Mobile prefix'),
        '#default_value' => '0032',
        '#disabled' => TRUE,
        '#states' => array(
          'visible' => array(
            ':input[name="commerce_shipping[service_details][bpack_account][account]"]' => array('value' => 'new'),
          ),
        ),
        '#element_validate' => array('_commerce_bpost_pane_value_hack'),
      );
      $form['bpack_account']['createmember']['mobilenumber'] = array(
        '#type' => 'textfield',
        '#title' => t('Mobile number'),
        '#description' => t('Expected format: 4xxxxxxxx'),
        '#default_value' => $commerce_customer_address->mobile_number->value(),
        '#states' => array(
          'visible' => array(
            ':input[name="commerce_shipping[service_details][bpack_account][account]"]' => array('value' => 'new'),
          ),
        ),
        '#element_validate' => array('_commerce_bpost_pane_value_hack'),
      );
      $form['bpack_account']['createmember']['language'] = array(
        '#type' => 'select',
        '#title' => t('Language'),
        '#options' => array(
          'nl-BE' => t('Dutch (Belgium)'),
          'fr-BE' => t('French (Belgium)'),
          'en-US' => t('English (USA)'),
        ),
        '#default_value' => '',
        '#states' => array(
          'visible' => array(
            ':input[name="commerce_shipping[service_details][bpack_account][account]"]' => array('value' => 'new'),
          ),
        ),
        '#element_validate' => array('_commerce_bpost_pane_value_hack'),
      );
      $form['bpack_account']['createmember']['general_conditions'] = array(
        '#type' => 'checkbox',
        '#title' => t('I agree with the !link', array('!link' => l(t('general condition'), 'http://www.bpost.be/site/nl/docs/conditions/Conditions_generales_bpack247_NL.pdf', array('attributes' => array('target' => '_blank'), 'external' => TRUE)))),
        '#default_value' => 0,
        '#states' => array(
          'visible' => array(
            ':input[name="commerce_shipping[service_details][bpack_account][account]"]' => array('value' => 'new'),
          ),
        ),
        '#element_validate' => array('_commerce_bpost_pane_value_hack'),
      );
    }
    else {
      $member = $order->data['commerce_bpost']['bpack_member'];

      // Favorite points
      $packstations = array();
      if (!empty($member['PackStations']['CustomerPackStation'])) {
        foreach ($member['PackStations'] as $packstation) {
          $point = commerce_bpost_get_point_details($packstation['PackstationID'], 4);
          $point['Poi']['Favorite'] = TRUE;
          $packstations[] = $point['Poi'];
        }
      }

      // Address
//      $customer_address['thoroughfare'] = $commerce_customer_address->thoroughfare->value();
      $customer_address['postal_code'] = $commerce_customer_address->postal_code->value();
      $customer_address['city'] = $commerce_customer_address->locality->value();
      $customer_address['country'] = $commerce_customer_address->country->value();

      // Customer address.
      if (!empty($pane_values['commerce_bpost']['filters']['postal_code']) ||
        !empty($pane_values['commerce_bpost']['filters']['city']) ||
        !empty($pane_values['commerce_bpost']['filters']['country'])
      ) {
        unset($pane_values['commerce_bpost']['filters']['submit']);
        $customer_address = $pane_values['commerce_bpost']['filters'];
      }

      // Points.
      $points = array_merge($packstations, commerce_bpost_webservice_get_nearest_service_points($customer_address, 4));
      $map_markers = array();
      $point_options = array();
      $point_favorite = NULL;
      if (!empty($points)) {
        foreach ($points as $point) {
          if (isset($point['Id'])) {
            $point['Record'] = $point;
          }
          if (isset($point['Record']['Id'])) {
            $id = $point['Record']['Id'];
            $icon = base_path() . drupal_get_path('module', 'commerce_bpost') . '/icons/bpost-point.png';
          }
          else {
            $id = $point['Record']['ID'];
            $icon = base_path() . drupal_get_path('module', 'commerce_bpost') . '/icons/bpost-point-favorite.png';
          }
          if (!empty($point['Record']['Latitude']) && !empty($point['Record']['Longitude']) && !empty($point['Record']['Type'])) {
            $map_markers[$id] = array(
              'coordGeolocalisationLatitude' => $point['Record']['Latitude'],
              'coordGeolocalisationLongitude' => $point['Record']['Longitude'],
              'identifiant' => $id,
              'infoWindow' => theme_commerce_bpost_point(array('point' => $point)),
              'icon' => $icon,
              'type' => $point['Record']['Type'],
            );
            $point_options[$point['Record']['Type'] . '|' . $id] = theme_commerce_bpost_point(array('point' => $point));
            if (!$point_favorite && isset($point['Favorite']) && $point['Favorite']) {
              $point_favorite = $point['Record']['Type'] . '|' . $id;
            }
          }
        }
      }

      $form['filters'] = array(
        '#type' => 'container',
        '#tree' => TRUE,
        '#attributes' => array(
          'class' => array(
            'container-inline',
            'commerce-bpost-filters',
          ),
        ),
        '#prefix' => '<div>',
      );
//      $form['filters']['thoroughfare'] = array(
//        '#type' => 'textfield',
//        '#title' => t('Thoroughfare'),
//        '#default_value' => isset($customer_address['thoroughfare']) ? $customer_address['thoroughfare'] : '',
//        '#size' => 30,
//        '#maxlength' => 64,
//        '#element_validate' => array('_commerce_bpost_pane_value_hack'),
//      );
      $form['filters']['postal_code'] = array(
        '#type' => 'textfield',
        '#title' => t('Postal code'),
        '#default_value' => isset($customer_address['postal_code']) ? $customer_address['postal_code'] : '',
        '#size' => 10,
        '#maxlength' => 10,
        '#element_validate' => array('_commerce_bpost_pane_value_hack'),
      );
      $form['filters']['city'] = array(
        '#type' => 'textfield',
        '#title' => t('City'),
        '#default_value' => isset($customer_address['city']) ? $customer_address['city'] : '',
        '#size' => 15,
        '#maxlength' => 32,
        '#element_validate' => array('_commerce_bpost_pane_value_hack'),
      );
      $form['filters']['country'] = array(
        '#type' => 'select',
        '#title' => t('Country'),
        '#default_value' => isset($customer_address['country']) ? $customer_address['country'] : '',
        '#options' => array('BE' => 'Belgium'),
        '#element_validate' => array('_commerce_bpost_pane_value_hack'),
      );
      $form['filters']['submit'] = array(
        '#type' => 'button',
        '#value' => t('Search'),
        '#ajax' => array(
          'callback' => 'commerce_bpost_pane_checkout_form_details_refresh',
          'wrapper' => 'commerce-shipping-service-details',
          'method' => 'replace',
        ),
      );
      $form['bpack_map'] = array(
        '#type' => 'fieldset',
        '#title' => t('Select a parcel locker'),
        '#weight' => 0,
        '#collapsible' => FALSE,
        '#collapsed' => FALSE,
        '#attributes' => array('id' => array('bpack-shipping-map')),
      );
      $form['bpack_map']['points'] = array(
        '#type' => 'container',
        '#attributes' => array(
          'id' => array('points-wrapper'),
          'class' => array('points-list'),
        ),
      );

      $form['bpack_map']['points']['points_list'] = array(
        '#type' => 'radios',
        '#title' => NULL,
        '#options' => $point_options,
        '#default_value' => $point_favorite,
        '#element_validate' => array('_commerce_bpost_pane_value_hack'),
        '#attributes' => array(
          'class' => array('points-list'),
        ),
      );

      // Map.
      $bpost_map = _commerce_bpost_map_settings();
      $bpost_map += array(
        'address' => implode(', ', $customer_address),
        'icons' => array(
          'domicile' => base_path() . drupal_get_path('module', 'commerce_bpost') . '/icons/domicile.png',
        ),
      );
      // Use json_encode to ensure markers array is reset javascript settings.
      $bpost_map += array('markers' => json_encode($map_markers));
      $form['bpack_map']['map'] = array(
        '#type' => 'commerce_bpost_map',
        '#map' => $bpost_map,
        '#attributes' => array(
          'class' => array('commerce-bpost-map'),
        ),
        '#prefix' => '<div class="map-container">',
        '#suffix' => '</div>',
      );
      $form['#attached']['css'][] = drupal_get_path('module', 'commerce_bpost') . '/theme/css/commerce_bpost.css';
      drupal_add_js(array('commerce_bpost_map' => $bpost_map), array('type' => 'setting'));

      $form['change_rc'] = array(
        '#type' => 'button',
        '#value' => t('Change bpack RC code'),
        '#ajax' => array(
          'callback' => 'commerce_bpost_check_bpack_member_ajax_callback',
          'wrapper' => 'delivery-parcel-automate',
          'method' => 'replace',
        ),
      );
    }

    $form['label'] = array(
      '#type' => 'value',
      '#value' => t('parcel locker'),
    );
  }
  else {
    $form['error'] = array(
      '#markup' => t('Commerce bpost module is not configured. Please contact the administrator.'),
    );
  }

  return $form;
}

/**
 * Ajax callback checking a bpack member.
 */
function commerce_bpost_check_bpack_member_ajax_callback($form, $form_state) {
  if ($form_state['values']['commerce_shipping']['service_details']['bpack_account']['account'] == 1) {
    return $form['commerce_shipping']['service_details']['bpack_map'];
  }
  else {
    return $form['commerce_shipping']['service_details'];
  }
}

/**
 * Shipping service bpack form validate.
 *
 * Checkout pane callback: validate bpack point is selected.
 */
function commerce_bpost_service_details_map_bpack_form_validate($details_form, $details_values, $shipping_service, $order, $form_parents) {
  if (isset($details_values['customer_profile'])) {
    commerce_bpost_service_details_form_validate($details_form, $details_values, $shipping_service, $order, $form_parents);
    if (!form_get_errors()) {
      $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
      _commerce_bpost_service_customer_profile_save($details_form, $details_values, $order_wrapper);
    }
    return FALSE;
  }
  elseif (isset($details_values['bpack_account'])) {
    $member = FALSE;
    switch ($details_values['bpack_account']['account']) {
      case 'new':
        if ($details_values['bpack_account']['createmember']['general_conditions'] == 0) {
          form_set_error("commerce_shipping][service_details][bpack_account][createmember][general_conditions", t('You must accept general terms and conditions.'));
          return FALSE;
        }
        elseif (!_commerce_bpost_valid_phone_number($details_values['bpack_account']['createmember']['mobilenumber'])) {
          form_set_error('commerce_shipping][service_details][bpack_account][createmember][mobilenumber', t('Please enter a valid phone number'));
          return FALSE;
        }

        // Create member
        $member = commerce_bpost_create_bpack_member($details_values['bpack_account']['createmember']);
        if (isset($member['error'])) {
          $error_field_name = 'commerce_shipping][service_details][bpack_account';
          if ($member['error']) {
            if (strpos($member['error'], 'Email incorrect format') !== FALSE) {
              $error_field_name = 'commerce_shipping][service_details][bpack_account][createmember][email';
              $member['error'] = t('Email format is incorrect.');
            }
            elseif (strpos($member['error'], 'MobileNumber incorrect format') !== FALSE) {
              $error_field_name = 'commerce_shipping][service_details][bpack_account][createmember][mobilenumber';
              $member['error'] = t('Mobile number format is incorrect.');
            }
          }
          $message = $member['error'] ? $member['error']: t('Something went wrong with your account creation. Please retry or contact the administrator.');
          form_set_error($error_field_name, filter_xss($message));
          $member = FALSE;
        }
        else {
          drupal_set_message(t('Your bpack account has been successfully created. RC code %rc', array('%rc' => $member['DeliveryCode'])));
        }
        break;
      case 'registered':
        if (empty($details_values['bpack_account']['member']['rc']) or !($member = commerce_bpost_check_bpack_member($details_values['bpack_account']['member']['rc']))) {
          // Check member
          form_set_error('commerce_shipping][service_details][bpack_account][member][rc', t('Please enter a valid bpack code'));
        }
        break;
      default:
          form_set_error('commerce_shipping][service_details][bpack_account][account', t('Please select if you are a registered parcel locker user or if you want to register.'));
        break;
    }

    if ($member) {
      // Save bpack member into commerce_order
      $member = json_decode(json_encode($member), TRUE);
      $order->data['commerce_bpost']['bpack_member'] = $member;
    }

    return FALSE;
  }
  else {
    $return = TRUE;
    if (isset($pane_values['commerce_bpost']['bpack_account']['account']) && $pane_values['commerce_bpost']['bpack_account']['account'] == 0) {
      foreach ($pane_values['commerce_bpost']['bpack_account']['createmember'] as $field => $value) {
        if (empty($pane_values['commerce_bpost']['bpack_account']['bpack_account']['createmember'][$field])) {
          form_set_error('commerce_bpost][bpack_account][bpack_account][createmember][' . $field, t('Please fill the field %field', array('%field' => $details_form['commerce_shipping']['service_details']['bpack_account']['createmember'][$field]['#title'])));
          return FALSE;
        }
      }
    }

    if (empty($details_values['bpack_map']['points']['points_list']) || (!empty($details_values['bpack_map']['points']['points_list']) && !preg_match('/^[0-9]+\|[0-9]+$/', $details_values['bpack_map']['points']['points_list']))) {
      form_set_error('commerce_bpost_point_id', t('Please select a @label', array('@label' => $details_values['label'])));
      $return = FALSE;
    }

    return $return;
  }
}

/**
 * Shipping service postpoint form callback.
 *
 * Checkout pane callback: postpoint selection.
 */
function commerce_bpost_service_details_map_form($pane_form, $pane_values, $checkout_pane, $order, $shipping_service) {
  $commerce_bpost_settings = variable_get('commerce_bpost_settings', array());
  if (commerce_bpost_check_minimal_config_requirement($commerce_bpost_settings)) {

    if ($form = commerce_bpost_service_details_form($pane_form, $pane_values, $checkout_pane, $order, $shipping_service)) {
      return $form;
    }

    $form = array(
      '#type' => 'container',
      '#attributes' => array(
        'class' => array('bpost-shipping-services'),
        'id' => array('pickup-postoffice-postpoint'),
      ),
    );

    // Address
    $wrapper_order = entity_metadata_wrapper('commerce_order', $order);
    $commerce_customer_address = $wrapper_order->commerce_customer_shipping->commerce_customer_address;
    $customer_address['thoroughfare'] = $commerce_customer_address->thoroughfare->value();
    $customer_address['premise'] = $commerce_customer_address->premise->value();
    $customer_address['postal_code'] = $commerce_customer_address->postal_code->value();
    $customer_address['city'] = $commerce_customer_address->locality->value();
    $customer_address['country'] = $commerce_customer_address->country->value();

    $label = t('PostOffice or PostPoint');
    // Customer address.
    if (!empty($pane_values['commerce_bpost']['filters']['postal_code']) ||
      !empty($pane_values['commerce_bpost']['filters']['city']) ||
      !empty($pane_values['commerce_bpost']['filters']['country'])
    ) {
      unset($pane_values['commerce_bpost']['filters']['submit']);
      $customer_address = $pane_values['commerce_bpost']['filters'];
    }
    $customer_address['phoneNumber'] = substr(commerce_bpost_get_field_value('phoneNumber', $wrapper_order->commerce_customer_shipping, $commerce_bpost_settings['mapping']['profile']['fields'], 'commerce_customer_profile'), 0, 20);

    // Points.
    $form['bpack_map'] = array(
      '#type' => 'container',
      '#attributes' => array(
        'id' => array('points-wrapper'),
      ),
    );
    $points = commerce_bpost_webservice_get_nearest_service_points($customer_address, 3);
    if (empty($points)) {
      unset($customer_address['thoroughfare']);
      unset($customer_address['premise']);
      drupal_set_message(t('Warning: No points was found with your address. The current search was made only by using your postcode. Try again if needed.'), 'warning');
      $points = commerce_bpost_webservice_get_nearest_service_points(array('postal_code' => $customer_address['postal_code']), 3);
    }

    $point_options = array();
    $map_markers = array();
    if (!empty($points)) {
      foreach ($points as $point) {
        $point_details = commerce_bpost_get_postpoint_hours($point['Info']['@attributes']['ServiceRef']);
        if (!empty($point_details['Poi']['Record']['Hours'])) {
          $point['Record']['Hours'] = $point_details['Poi']['Record']['Hours'];
        }
        $map_markers[$point['Record']['Id']] = array(
          'coordGeolocalisationLatitude' => $point['Record']['Latitude'],
          'coordGeolocalisationLongitude' => $point['Record']['Longitude'],
          'identifiant' => $point['Record']['Id'],
          'infoWindow' => theme_commerce_bpost_point(array('point' => $point)),
          'icon' => base_path() . drupal_get_path('module', 'commerce_bpost') . '/icons/bpost-point.png',
          'type' => $point['Record']['Type'],
        );
        $point_options[$point['Record']['Type'] . '|' . $point['Record']['Id']] = theme_commerce_bpost_point(array('point' => $point, 'schedule' => FALSE));
      }
    }
    else {
      $form['bpack_map']['nopoint'] = array(
        '#markup' => '<div class="noaddress">' . t('There is no') . ' ' . $label . ' ' . t('available for this address.') . '</div>',
      );
    }
    $form['label'] = array(
      '#type' => 'value',
      '#value' => $label,
    );
    $form['filters'] = array(
      '#type' => 'container',
      '#tree' => TRUE,
      '#attributes' => array(
        'class' => array(
          'container-inline',
          'commerce-bpost-filters',
        ),
      ),
      '#prefix' => '<div class="map-container">'
    );
    $form['filters']['postal_code'] = array(
      '#type' => 'textfield',
      '#title' => t('Postal code'),
      '#default_value' => $customer_address['postal_code'],
      '#size' => 10,
      '#maxlength' => 10,
      '#element_validate' => array('_commerce_bpost_pane_value_hack'),
    );
    $form['filters']['city'] = array(
      '#type' => 'textfield',
      '#title' => t('City'),
      '#default_value' => $customer_address['city'],
      '#size' => 15,
      '#maxlength' => 32,
      '#element_validate' => array('_commerce_bpost_pane_value_hack'),
    );
    $form['filters']['country'] = array(
      '#type' => 'select',
      '#title' => t('Country'),
      '#default_value' => $customer_address['country'],
      '#options' => array('BE' => 'Belgium'),
      '#element_validate' => array('_commerce_bpost_pane_value_hack'),
    );
    $form['filters']['submit'] = array(
      '#type' => 'button',
      '#value' => t('Search'),
      '#ajax' => array(
        'callback' => 'commerce_bpost_pane_checkout_form_details_refresh',
        'wrapper' => 'commerce-shipping-service-details',
        'method' => 'replace',
      ),
    );
    $form['bpack_map']['points']['points_list'] = array(
      '#type' => 'radios',
      '#options' => $point_options,
      '#attributes' => array(
        'class' => array('points-list'),
      ),
    );
    // Map.
    $bpost_map = _commerce_bpost_map_settings();
    $bpost_map += array(
      'address' => implode(', ', $customer_address),
      'icons' => array(
        'domicile' => base_path() . drupal_get_path('module', 'commerce_bpost') . '/icons/domicile.png',
      ),
    );

    // Use json_encode to ensure markers array is reset javascript settings.
    $bpost_map += array('markers' => json_encode($map_markers));
    $form['map'] = array(
      '#type' => 'commerce_bpost_map',
      '#map' => $bpost_map,
      '#attributes' => array(
        'class' => array('commerce-bpost-map'),
      ),
      '#suffix' => '</div>', // closing #map-container.
    );

    $form['#attached']['css'][] = drupal_get_path('module', 'commerce_bpost') . '/theme/css/commerce_bpost.css';
    drupal_add_js(array('commerce_bpost_map' => $bpost_map), array('type' => 'setting'));

    $form['notification_message'] = array(
      '#type' => 'radios',
      '#title' => t('Keep me informed via'),
      '#options' => array(
        'phone' => t('Sms'),
        'mail' => t('Email'),
      ),
    );
    $form['notification_message_phone'] = array(
      '#title' => t('Phone Number'),
      '#type' => 'textfield',
      '#states' => array(
        'visible' => array(':input[name="commerce_shipping[service_details][notification_message]"]' => array('value' => 'phone')),
        'required' => array(':input[name="commerce_shipping[service_details][notification_message]"]' => array('value' => 'phone'))
      ),
      '#default_value' => !empty($customer_address['phoneNumber']) ? $customer_address['phoneNumber'] : '',
    );

  }
  else {
    $form['error'] = array(
      '#markup' => t('Commerce bpost module is not configured. Please contact the administrator.'),
    );
  }

  return $form;
}

/**
 * Returns the payment details element for display via AJAX.
 */
function commerce_bpost_pane_checkout_form_details_refresh($form, $form_state) {
  return $form['commerce_shipping']['service_details'];
}

/**
 * Shipping service pospoint form validate.
 *
 * Checkout pane callback: validate postpoint is selected.
 */
function commerce_bpost_service_details_map_postpoint_form_validate($details_form, $details_values, $shipping_service, $order, $form_parents) {
  if (isset($details_values['customer_profile'])) {
    commerce_bpost_service_details_form_validate($details_form, $details_values, $shipping_service, $order, $form_parents);
    if (!form_get_errors()) {
      $line_item_wrapper = _commerce_bpost_get_shipping_line_item($order);
      commerce_bpost_service_details_form_submit($details_form, $details_values, $line_item_wrapper->value());
      return FALSE;
    }
  }
  else {
    $return = TRUE;
    if (empty($details_values['notification_message'])) {
      form_set_error('notification_message_phone', t('Keep me informed via field is required.'));
      $return = FALSE;
    }
    elseif ($details_values['notification_message'] == "phone"
      && !_commerce_bpost_valid_phone_number($details_values['notification_message_phone'])
    ) {
      form_set_error('notification_message_phone', t('Please enter a valid phone number'));
      $return = FALSE;
    }
    if (empty($details_values['bpack_map']['points']['points_list'])) {
      form_set_error('commerce_bpost_point_id', t('Please select a @label', array('@label' => $details_values['label'])));
      $return = FALSE;
    }
    else {
      $point = explode('|', $details_values['bpack_map']['points']['points_list']);
      $point_details = commerce_bpost_get_point_details($point[1], $point[0]);
      if (!empty($point_details)) {
        $order->data['commerce_bpost']['point_details'] = $point_details;
        commerce_order_save($order);
      }
      else {
        form_set_error('commerce_bpost_point_id', t('An error occured, please try again or contact the administrator.'));
        $return = FALSE;
      }
    }

    return $return;
  }
}

/**
 * Shipping service postpoint & bpack form submit.
 *
 * Checkout pane callback: save post or bpack delivery point
 *   in the shipping line item.
 */
function commerce_bpost_service_details_map_form_submit($details_form, $details_values, $line_item) {
  // Save the point address into the line_item.
  $point = explode('|', $details_values['bpack_map']['points']['points_list']);
  $point_details = commerce_bpost_get_point_details($point[1], $point[0]);
  $line_item_wrapper = entity_metadata_wrapper('commerce_line_item', $line_item);
  if (!empty($point_details)) {
    $line_item_wrapper->value()->data['point_details'] = $point_details;
    if (!empty($line_item_wrapper->order->value()->data['commerce_bpost']['bpack_member']['DeliveryCode'])) {
      $line_item_wrapper->value()->data['bpack_member'] = $line_item_wrapper->order->value()->data['commerce_bpost']['bpack_member']['DeliveryCode'];
      unset($line_item_wrapper->order->value()->data['commerce_bpost']);
    }
  }
  if (isset($details_values['notification_message'])) {
    $line_item_wrapper->value()->data['notification_message'] = $details_values['notification_message'];
    $line_item_wrapper->value()->data['notification_message_phone'] = $details_values['notification_message_phone'];
  }
}

/**
 * Implements hook_commerce_checkout_pane_info().
 */
function commerce_bpost_commerce_checkout_pane_info() {
  $checkout_panes = array();

  $checkout_panes['commerce_bpost_shipping_profile'] = array(
    'title' => t('bpost shipping'),
    'file' => 'includes/commerce_bpost.checkout_pane.inc',
    'base' => 'commerce_bpost_pane',
    'page' => 'checkout',
    'weight' => 8,
  );

  return $checkout_panes;
}

function commerce_bpost_get_postpoint_hours($url) {
  $xml = simplexml_load_string(file_get_contents('http://taxipost.geo6.be/Locator?Function=info&Partner=999999&AppId=&Id=9800&Type=1&Language=NL'));
  $xml = json_decode(json_encode($xml), 1);
  return $xml;
}

/**
 * Check phone number is valid for belgium.
 *
 * @param string $phone
 * Phone number to check.
 *
 * @return bool
 */
function _commerce_bpost_valid_phone_number($phone) {
  // Valid phone numbers are :
  // 04xxxxxxxx
  // +324xxxxxxxx
  // 4xxxxxxxx
  // 324xxxxxxxx
  // 00324xxxxxxxx
  if (empty($phone)
      || !preg_match('/^(((\+|00)?32)|0)?4[0-9]{8}$/', $phone)
    ) {
    return FALSE;
  }
  return TRUE;
}