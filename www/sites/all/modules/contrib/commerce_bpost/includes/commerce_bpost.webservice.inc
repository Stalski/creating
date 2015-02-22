<?php
/**
 * @file
 * Define webservices methods to call Bpost services.
 */

/**
 * This function send a request to bpost Webservice.
 *
 * @param string $service
 *   The service we request.
 * @param array $options
 *   The options for drupal_http_request second arguments.
 * @param string $url
 *   The base url if different than the one set on the administration page.
 *
 * @return array
 */
function commerce_bpost_request_bpost($service, $options = array(), $url = '') {
  $commerce_bpost_settings = variable_get('commerce_bpost_settings');
  if (empty($url)) {
    $url = commerce_bpost_get_bpost_base_url() . $service;
  }
  else {
    $url .= $service;
  }
  $authorization = isset($commerce_bpost_settings['account']['account_id']) ? $commerce_bpost_settings['account']['account_id'] : '';
  $authorization .= ':';
  $authorization .= isset($commerce_bpost_settings['account']['passphrase']) ? $commerce_bpost_settings['account']['passphrase'] : '';
  $options += array(
    'method' => 'GET',
    'headers' => array(),
  );
  $options['headers'] += array('Authorization' => 'Basic ' . base64_encode($authorization));

  return drupal_http_request($url, $options);
}

/**
 * Get base url for making calls with bpost WS.
 *
 * @return string
 *  Return the base url.
 */
function commerce_bpost_get_bpost_base_url() {
  $commerce_bpost_settings = variable_get('commerce_bpost_settings');
  return !empty($commerce_bpost_settings['account']['api_url']) ? $commerce_bpost_settings['account']['api_url'] : '';
}

/**
 * Validate API credentials
 *
 * @param string $login
 *   API login
 * @param string $pass
 *   API pass
 * @param string $url
 *   API url
 *
 * @return bool
 *   Whether credentials are valid or not.
 */
function commerce_bpost_webservice_validate_credentials($login, $pass, $url) {
  $offset = 0;
  $parsed_url = parse_url($url);
  if (!isset($parsed_url['scheme'])) {
    $parsed_url['scheme'] = 'http';
  }
  else {
    $offset = drupal_strlen($parsed_url['scheme']) + 3;
  }
  $response = commerce_bpost_request_bpost(NULL, array(), $parsed_url['scheme'] . '://' . $login . ':' . $pass . '@' . substr($url, $offset));

  switch ($response->code) {
    case 405:
      /**
       * 405 (Method Not Allowed) is the valid code for
       * https://api.bpost.be/services/shm since we don't provide
       * the method to call
       * Otherwise we hit a 401 error code if the Authorization is invalid
       */
      $valid = TRUE;
      break;
    default:
      $valid = FALSE;
  }
  variable_set('commerce_bpost_credentials', $valid);
  return $valid;
}

function commerce_bpost_webservice_create_order($order, $order_type, $options = array()) {
  $options += array(
    'return' => FALSE,
    'send_only' => FALSE,
  );
  $commerce_bpost_settings = variable_get('commerce_bpost_settings', array());
  $field_mapping = $commerce_bpost_settings['mapping']['profile']['fields'];
  $order_wrapper = entity_metadata_wrapper($order_type, $order);
  switch ($order_type) {
    case 'commerce_order':
      $customer_address = $order_wrapper->commerce_customer_shipping;
      $customer_address = array(
        'name' => commerce_bpost_get_field_value('name', $customer_address, $field_mapping, 'commerce_customer_profile'),
        'company' => commerce_bpost_get_field_value('company', $customer_address, $field_mapping, 'commerce_customer_profile'),
        'streetName' => substr(commerce_bpost_get_field_value('streetName', $customer_address, $field_mapping, 'commerce_customer_profile'), 0, 40),
        'number' => substr(commerce_bpost_get_field_value('number', $customer_address, $field_mapping, 'commerce_customer_profile'), 0, 40),
        'box' => substr(commerce_bpost_get_field_value('box', $customer_address, $field_mapping, 'commerce_customer_profile'), 0, 8),
        'postalCode' => substr(commerce_bpost_get_field_value('postalCode', $customer_address, $field_mapping, 'commerce_customer_profile'), 0, 40),
        'locality' => substr(commerce_bpost_get_field_value('locality', $customer_address, $field_mapping, 'commerce_customer_profile'), 0, 40),
        'mail' => substr($customer_address->user->mail->value(), 0, 50),
        'countryCode' => substr(commerce_bpost_get_field_value('countryCode', $customer_address, $field_mapping, 'commerce_customer_profile'), 0, 2),
      );
      $country_code = $customer_address['countryCode'];
      $sender_address = $commerce_bpost_settings['mapping']['sender'];
      $line_item_field = 'commerce_line_items';
      $total_field = 'commerce_order_total';
      $original_order = $order_wrapper;
      $weight = commerce_physical_order_weight($order, 'g');
      break;
    default:
      return FALSE;
  }

  if ($options['return']) {
    $tmp = $sender_address;
    $sender_address = $customer_address;
    $customer_address = $tmp;
    unset($tmp);
  }

  if (!$weight) {
    $weight = array('weight' => 10);
  }

  foreach ($original_order->commerce_line_items as $line_item_wrapper) {
    if ($line_item_wrapper->getBundle() == 'shipping') {
      $line_item = $line_item_wrapper->value();
      if ($line_item->data['shipping_service']['shipping_method'] == 'bpost') {
        $shipping_line_item = $line_item_wrapper;
      }
    }
  }
  if (!isset($shipping_line_item, $sender_address)) {
    watchdog('commerce_bpost', 'Webservice > createOrder method: required data not found. Nothing has been sent.', array(), WATCHDOG_ERROR);
    return FALSE;
  }
  else {
    $shipping_item_data = $shipping_line_item->value();
    if (!empty($shipping_item_data->data['notification_message_phone'])) {
      $customer_address['phoneNumber'] = $shipping_item_data->data['notification_message_phone'];
    }
    else {
      $customer_address['phoneNumber'] = substr(commerce_bpost_get_field_value('phoneNumber', $order_wrapper->commerce_customer_shipping, $field_mapping, 'commerce_customer_profile'), 0, 20);
    }
  }
  $shipping_product = commerce_bpost_get_shipping_product($shipping_line_item->commerce_shipping_service->value(), $country_code, $options['return']);
  $xml = new XMLWriter();
  $xml->openMemory();
  $xml->startDocument('1.0', 'UTF-8');
  $xml->startElement('tns:order');
  $xml->writeAttribute('xmlns', 'http://schema.post.be/shm/deepintegration/v3/national');
  $xml->writeAttribute('xmlns:common', 'http://schema.post.be/shm/deepintegration/v3/common');
  $xml->writeAttribute('xmlns:tns', 'http://schema.post.be/shm/deepintegration/v3/');
  $xml->writeAttribute('xmlns:international', 'http://schema.post.be/shm/deepintegration/v3/international');
  $xml->writeAttribute('xmlns:xsi', 'http://www.w3.org/2001/XMLSchema-instance');
  $xml->writeAttribute('xsi:schemaLocation', 'http://schema.post.be/shm/deepintegration/v3/');

  $xml->writeElement('tns:accountId', $commerce_bpost_settings['account']['account_id']);
  $xml->writeElement('tns:reference', _commerce_bpost_get_bpost_id($order));
  $drupal_version = constant('VERSION');
  if (!empty($drupal_version)) {
    $xml->writeElement('tns:costCenter', 'DRU_' . $drupal_version);
  }
  // Line items
  foreach ($order_wrapper->$line_item_field as $line_item) {
    if ($line_item->getBundle() == 'product') {
      $xml->startElement('tns:orderLine');
        $xml->writeElement('tns:text', substr($line_item->commerce_product->title->value(), 0, 50));
        $xml->writeElement('tns:nbOfItems', (int) $line_item->quantity->value());
      $xml->endElement();
    }
  }

  // Merchant shipping address
  $xml->startElement('tns:box');
    $xml->startElement('tns:sender');
      $xml->writeElement('common:name', $sender_address['name']);
      if (!empty($sender_address['company'])) {
        $xml->writeElement('common:company', $sender_address['company']);
      }
      $xml->startElement('common:address');
        $xml->writeElement('common:streetName', $sender_address['streetName']);
        $xml->writeElement('common:number', substr($sender_address['number'], 0, 8));
        if (!empty($sender_address['box'])) {
          $xml->writeElement('common:box', $sender_address['box']);
        }
        $xml->writeElement('common:postalCode', $sender_address['postalCode']);
        $xml->writeElement('common:locality', $sender_address['locality']);
        $xml->writeElement('common:countryCode', $sender_address['countryCode']);
      $xml->endElement();
      if (!empty($sender_address['mail'])) {
        $xml->writeElement('common:emailAddress', $sender_address['mail']);
      }
      if (isset($customer_address['phoneNumber']) && !empty($sender_address['phoneNumber'])) {
        $xml->writeElement('common:phoneNumber', $sender_address['phoneNumber']);
      }
    $xml->endElement();

  // Customer shipping address & service
  $shipping_service_name = $shipping_line_item->commerce_shipping_service->value();
  if ($options['return'] && $shipping_service_name != 'bpost_world') {
    $shipping_service_name = 'bpost_home';
  }
  switch ($shipping_service_name) {
    case 'bpost_home':
        $xml->startElement('tns:nationalBox');
        $xml->startElement('atHome');
          $xml->writeElement('product', $shipping_product);
          $xml->startElement('options');
          if (!$options['return'] && !empty($commerce_bpost_settings['options']['bpost_home']['second_presentation'])) {
            $xml->writeElement('common:automaticSecondPresentation', '');
          }
          if (!$options['return'] && !empty($commerce_bpost_settings['options']['bpost_home']['insurance'])) {
            $xml->startElement('common:insured');
              $xml->writeElement('common:basicInsurance', '');
            $xml->endElement();
          }
          elseif (!$options['return'] && !empty($commerce_bpost_settings['options']['bpost_home']['signature'])) {
            $xml->writeElement('common:signed', '');
          }
//          $xml->writeElement('common:infoDistributed', '');
//          $xml->writeElement('infoNextDay', '');
//          $xml->writeElement('infoReminder', '');
//          $xml->writeElement('cod', '');
//          $xml->writeElement('signed', '');
//          $xml->writeElement('insured', '');
        $xml->endElement();
          $xml->writeElement('weight', $weight['weight']);
//          if ($key == 'bpack_24_business') {
//            $xml->writeElement('openingHours', '');
//            $xml->writeElement('desiredDeliveryPlace', '');
//          }
          $xml->startElement('receiver');
            $xml->writeElement('common:name', $customer_address['number']);
            $xml->writeElement('common:company', $customer_address['name']);
            $xml->startElement('common:address');
              $xml->writeElement('common:streetName', $customer_address['streetName']);
              $xml->writeElement('common:number', '.');
              if ($customer_address['box']) {
                $xml->writeElement('common:box', $customer_address['box']);
              }
              $xml->writeElement('common:postalCode', $customer_address['postalCode']);
              $xml->writeElement('common:locality', $customer_address['locality']);
              $xml->writeElement('common:countryCode', $customer_address['countryCode']);
            $xml->endElement();
            if ($customer_address['mail']) {
              $xml->writeElement('common:emailAddress', $customer_address['mail']);
            }
            if (isset($customer_address['phoneNumber']) && $customer_address['phoneNumber']) {
              $xml->writeElement('common:phoneNumber', $customer_address['phoneNumber']);
            }
          $xml->endElement();
        $xml->endElement();
        $xml->endElement();
        break;
      case 'bpost_world':
        $xml->startElement('tns:internationalBox');
          $xml->startElement('international:international');
            $xml->writeElement('international:product', $shipping_product);
            if (!empty($commerce_bpost_settings['options']['bpost_world']['insurance_basic'])) {
              $xml->startElement('international:options');
              if (!$options['return'] && !empty($commerce_bpost_settings['options']['bpost_world']['insurance_basic'])) {
                $xml->startElement('common:insured');
                  $xml->writeElement('common:basicInsurance', '');
                $xml->endElement();
              }
    //              if ($key == 'bpack_europe_business') {
    //                $xml->writeElement('automaticSecondPresentation', '');
    //              }
              $xml->endElement();
//              $xml->writeElement('receiverName', $customer_address['name']);
//              $xml->writeElement('receiverCompany', $customer_address['company']);
            }
            $xml->startElement('international:receiver');
              $xml->writeElement('common:name', $customer_address['number']);
              $xml->writeElement('common:company', $customer_address['name']);
              $xml->startElement('common:address');
              $xml->writeElement('common:streetName', $customer_address['streetName']);
              $xml->writeElement('common:number', '.');
              if ($customer_address['box']) {
                $xml->writeElement('common:box', $customer_address['box']);
              }
              $xml->writeElement('common:postalCode', $customer_address['postalCode']);
              $xml->writeElement('common:locality', $customer_address['locality']);
              $xml->writeElement('common:countryCode', $customer_address['countryCode']);
              $xml->endElement();
              if ($customer_address['mail']) {
                $xml->writeElement('common:emailAddress', $customer_address['mail']);
              }
              if (isset($customer_address['phoneNumber']) && $customer_address['phoneNumber']) {
                $xml->writeElement('common:phoneNumber', $customer_address['phoneNumber']);
              }
            $xml->endElement();
            $xml->writeElement('international:parcelWeight', $weight['weight']);
            if ($shipping_product != 'bpack Europe Business') {
              $shipment_type = array(
                'sample' => 'SAMPLE',
                'gift' => 'GIFT',
                'documents' => 'DOCUMENTS',
                'other' => 'OTHER'
              );
              $return_instructions = array(
                'rta' => 'RTA',
                'rts' => 'RTS',
                'abandoned' => 'ABANDONED',
              );
              $xml->startElement('international:customsInfo');
                $xml->writeElement('international:parcelValue', $order_wrapper->$total_field->amount->value());
                // Aggregate all product title to get a content description.
                $content_description = NULL;
                foreach ($order_wrapper->$line_item_field as $line_item) {
                  if ($line_item->getBundle() == 'product') {
                    $content_description .= $line_item->commerce_product->sku->value() . ",";
                  }
                }
                if (!empty($content_description)) {
                  $content_description = substr($content_description, 0, -1);
                }
                $xml->writeElement('international:contentDescription', substr($content_description, 0, 50));
                $xml->writeElement('international:shipmentType', $shipment_type['documents']);
                $xml->writeElement('international:parcelReturnInstructions', $return_instructions['rts']);
                $xml->writeElement('international:privateAddress', 'false');
              $xml->endElement();
            }
          $xml->endElement();
        $xml->endElement();
      break;
    case 'bpost_postoffice_postpoint':
      $xml->startElement('tns:nationalBox');
      $xml->startElement('atBpost');
        $xml->writeElement('product', $shipping_product);
        $xml->startElement('options');
          $xml->startElement('common:keepMeInformed');
            $xml->writeAttribute('language', commerce_bpost_get_current_language());
            if ($shipping_item_data->data['notification_message'] == "phone") {
              $xml->writeElement('common:mobilePhone', $customer_address['phoneNumber']);
            }
            else {
              $xml->writeElement('common:emailAddress', $customer_address['mail']);
            }
          $xml->endElement();
          if (!empty($commerce_bpost_settings['options']['bpost_postoffice_postpoint']['insurance'])) {
            $xml->startElement('common:insured');
              $xml->writeElement('common:basicInsurance', '');
            $xml->endElement();
          }
//          $xml->writeElement('infoDistributed', '');
//          $xml->writeElement('infoNextDay', '');
//          $xml->writeElement('cod', '');
//          $xml->writeElement('insured', '');
        $xml->endElement();
        $xml->writeElement('weight', $weight['weight']);
        //@TODO Complete with webservice info.
        $xml->writeElement('pugoId', $shipping_item_data->data['point_details']['Query']['Id']);
        $xml->writeElement('pugoName', $shipping_item_data->data['point_details']['Poi']['Record']['OFFICE']);
        $xml->startElement('pugoAddress');
          $xml->writeElement('common:streetName', substr($shipping_item_data->data['point_details']['Poi']['Record']['STREET'], 0, 40));
          $xml->writeElement('common:number', substr($shipping_item_data->data['point_details']['Poi']['Record']['NR'], 0, 8));
//          if ($customer_address['box']) {
//            $xml->writeElement('common:box', $customer_address['box']);
//          }
          $xml->writeElement('common:postalCode', substr($shipping_item_data->data['point_details']['Poi']['Record']['ZIP'], 0, 40));
          $xml->writeElement('common:locality', substr($shipping_item_data->data['point_details']['Poi']['Record']['CITY'], 0, 40));
          $xml->writeElement('common:countryCode', 'BE');
        $xml->endElement();
        $xml->writeElement('receiverName', $customer_address['name']);
        $xml->writeElement('receiverCompany', $customer_address['company']);
      $xml->endElement();
      $xml->endElement();
      break;
    case 'bpost_bpack':
      $xml->startElement('tns:nationalBox');
      $xml->startElement('at24-7');
        $xml->writeElement('product', $shipping_product);
        $xml->startElement('options');
//          $xml->startElement('common:infoDistributed');
//            $xml->writeAttribute('language', 'EN');
//            //$xml->writeElement('mobilePhone', '');
//            $xml->writeElement('common:emailAddress', $customer_address['mail']);
//          $xml->endElement();
//          $xml->startElement('common:infoNextDay');
//            $xml->writeAttribute('language', 'EN');
//            //$xml->writeElement('mobilePhone', '');
//            $xml->writeElement('common:emailAddress', $customer_address['mail']);
//          $xml->endElement();
//          $xml->writeElement('common:cod', '');
          if (!empty($commerce_bpost_settings['options']['bpost_bpack']['insurance'])) {
            $xml->startElement('common:insured');
              $xml->writeElement('common:basicInsurance');
            $xml->endElement();
          }
        $xml->endElement();
        $xml->writeElement('weight', $weight['weight']);
        // @TODO Complete with webservice info.
        $xml->writeElement('parcelsDepotId', !empty($shipping_line_item->value()->data['point_details']['Query']['Id']) ? sprintf("%06d", $shipping_line_item->value()->data['point_details']['Query']['Id']) : '');
        $xml->writeElement('parcelsDepotName', !empty($shipping_line_item->value()->data['point_details']['Poi']['Record']['OFFICE']) ? $shipping_line_item->value()->data['point_details']['Poi']['Record']['OFFICE'] : '');
        $xml->startElement('parcelsDepotAddress');
          $xml->writeElement('common:streetName', $customer_address['streetName']);
          $xml->writeElement('common:number', substr($customer_address['number'], 0, 8));
//          if ($value = commerce_bpost_get_field_value('box', $customer_address, $field_mapping, 'commerce_customer_profile')) {
//            $xml->writeElement('common:box', substr($value, 0, 8));
//          }
          $xml->writeElement('common:postalCode', $customer_address['postalCode']);
          $xml->writeElement('common:locality', $customer_address['locality']);
          $xml->writeElement('common:countryCode', $customer_address['countryCode']);
        $xml->endElement();
        $xml->writeElement('memberId', !empty($shipping_line_item->value()->data['bpack_member']) ? $shipping_line_item->value()->data['bpack_member'] : '');
        $xml->writeElement('receiverName', $customer_address['name']);
        $xml->writeElement('receiverCompany', $customer_address['company']);
      $xml->endElement();
      $xml->endElement();
      break;
    default:
      watchdog('commerce_bpost', 'Webservice > createOrder method: shipping service do not match. Nothing has been sent.', array(), WATCHDOG_ERROR);
      return FALSE;
  }
  $xml->endElement();

  $xml->endDocument();
  $xml = $xml->outputMemory();

  // Call the webservice
  $request_options = array(
    'method' => 'POST',
    'data' => $xml,
    'headers' => array(
      'Content-Type' => 'application/vnd.bpost.shm-order-v3+XML',
    ),
  );
  watchdog('commerce_bpost', 'Webservice > createOrder method: request for order n°!order_id.', array('!order_id' => $order_wrapper->getIdentifier()));
  $response = commerce_bpost_request_bpost('orders', $request_options, 'https://api.bpost.be/services/shm/' . $commerce_bpost_settings['account']['account_id'] . '/');

  if ($response->code == 201) {
    watchdog('commerce_bpost', 'Webservice > createOrder method: success.');
    if ($options['send_only']) {
      $order->type = 'commerce_order';
      return TRUE;
    }

    if (isset($response->headers['location'])) {
      preg_match('#https://api.bpost.be/services/shm/\d+/orders/(\w+)#', $response->headers['location'], $matches);
      if (isset($matches[1])) {
        _commerce_bpost_set_bpost_id($order, $matches[1]);
      }
    }
    return TRUE;
  }
  else {
    $error = simplexml_load_string($response->data);
    if ($error) {
      $error_msg = (string) $error->error;
    }
    else {
      $error_msg = $response->data;
    }
    drupal_set_message(t('An error occured while sending order n°@order_id to bpost: @error_msg', array('@order_id' => $order_wrapper->getIdentifier(), '@error_msg' => $error_msg)), 'error');
    watchdog('commerce_bpost', 'Webservice > createOrder method: error !code > @error_msg.', array('!code' => $response->code, ));
  }

  return FALSE;
}

function commerce_bpost_webservice_cancel_order($order) {
  $commerce_bpost_settings = variable_get('commerce_bpost_settings');
  if (!empty($commerce_bpost_settings['mapping']['canceling_status'])) {
    $order->status = $commerce_bpost_settings['mapping']['canceling_status'];
  }
  if (isset($commerce_bpost_settings['account']['account_id'])) {
    $xml = new XMLWriter();
    $xml->openMemory();
    $xml->startDocument('1.0', 'UTF-8');
    $xml->startElement('orderUpdate');
    $xml->writeAttribute('xmlns', 'http://schema.post.be/shm/deepintegration/v3/');
    $xml->writeAttribute('xmlns:xsi', 'http://www.w3.org/2001/XMLSchema-instance');
    $xml->writeAttribute('xsi:schemaLocation', 'http://schema.post.be/shm/deepintegration/v3/');
    $xml->writeElement('status', 'CANCELLED');
    $xml->endElement();
    $xml = $xml->outputMemory();
    $options = array(
      'method' => 'POST',
      'data' => $xml,
      'headers' => array(
        'Content-Type' => 'application/vnd.bpost.shm-orderUpdate-v3+XML',
      ),
    );
    $bpost_id = _commerce_bpost_get_bpost_id($order);
    watchdog('commerce_bpost', 'Webservice > cancelOrder method: request for order n°!order_id.', array('!order_id' => $order->order_id));
    $response = commerce_bpost_request_bpost('orders/' . $bpost_id, $options, 'https://api.bpost.be/services/shm/' . $commerce_bpost_settings['account']['account_id'] . '/');
    if ($response->code == 200) {
      watchdog('commerce_bpost', 'Webservice > cancelOrder method: order n°@order_id cancelled.', array('@order_id' => $order->order_id));
      drupal_set_message(t('Order @order_id cancelled', array('@order_id' => $order->order_id)));
    }
    else {
      watchdog('commerce_bpost', 'Webservice > cancelOrder method: Error while cancelling order n°!order_id.', array('!order_id' => $order->order_id));
      drupal_set_message(t('Error while cancelling order @order_id', array('@order_id' => $order->order_id)), 'error');
    }
  }
}


function commerce_bpost_webservice_get_nearest_service_points($address, $type) {
  global $language;
  $point_list = array();
  // Settings.
  $get = array(
    'Function' => 'search',
    'Partner' => '999999',
    'AddId' => 'A001',
  );

  // Language.
  if ($language->language == "FR" || $language->language == "NL") {
    $get['Language'] = $language->language;
  }
  else {
    $get['Language'] = 'NL';
  }

  // Address.
  if (!empty($address['thoroughfare'])) {
    $get['Street'] = $address['thoroughfare'];
  }
  if (!empty($address['postal_code'])) {
    $get['Zone'] = $address['postal_code'];
  }
  elseif (!empty($address['city'])) {
    $get['Zone'] = $address['city'];
  }
  //$get .= '&Number=';

  // Postoffice = 1, Post point = 2, Postoffice-PostPoint = 3, Bpack = 4.
  $get['Type'] = $type;
  $get['Limit'] = 10;

  $options = array(
    'method' => 'GET',
    'headers' => array(
      'Content-Type' => 'text/xml; charset=utf-8',
    ),
  );

  $get = drupal_http_build_query($get);

  watchdog('commerce_bpost', 'Webservice > get_nearest_service_points method: request sent.');
  $response = commerce_bpost_request_bpost($get, $options, 'http://taxipost.geo6.be/Locator?');
  watchdog('commerce_bpost', 'Webservice > get_nearest_service_points method: reply with code !code.', array('!code' => $response->code));
  if ($response->code == 200) {
    $responsetoarray = json_decode(json_encode((array) simplexml_load_string($response->data)), 1);
    if (!empty($responsetoarray['PoiList'])) {
      foreach ($responsetoarray['PoiList']['Poi'] as $point) {
        $point_list[] = $point;
      }
    }
  }
  return $point_list;
}

function commerce_bpost_check_bpack_member($rc) {
  $commerce_bpost_settings = variable_get('commerce_bpost_settings');
  $options = array();
  if (!empty($commerce_bpost_settings['account']['bpack_user']) && !empty($commerce_bpost_settings['account']['bpack_passkey'])) {
    $options['headers']['Authorization'] = 'Basic ' . base64_encode($commerce_bpost_settings['account']['bpack_user'] . ':' . $commerce_bpost_settings['account']['bpack_passkey']);
  }
  watchdog('commerce_bpost', 'Webservice > check_bpack_member method: request sent for client n°!back_number.', array('!bpack_number' => $rc));
  $response = commerce_bpost_request_bpost($rc, $options, $commerce_bpost_settings['account']['bpack_url'] . '/');
  watchdog('commerce_bpost', 'Webservice > check_bpack_member method: reply with code !code.', array('!code' => $response->code));
  if ($response->code == 200) {
    $xml = new SimpleXMLElement($response->data);
    return (array) $xml;
  }
  else {
    return FALSE;
  }
}

function commerce_bpost_create_bpack_member($member) {
  $commerce_bpost_settings = variable_get('commerce_bpost_settings');
  $xml = new XMLWriter();
  $xml->openMemory();
  $xml->startDocument('1.0', 'UTF-8');
  $xml->startElement('Customer');
  $xml->writeAttribute('xmlns', 'http://schema.post.be/ServiceController/customer');
  $xml->writeAttribute('xmlns:xsi', 'http://www.w3.org/2001/XMLSchema-instance');
  $xml->writeAttribute('xsi:schemaLocation', 'http://schema.post.be/ServiceController/customerC:\Tmp\ShippingModule\Phase2\Analysis\Packstation\BPost_xsd_files\CustomerValidation.xsd');
    $xml->writeElement('FirstName', $member['firstname']);
    $xml->writeElement('LastName', $member['lastname']);
    $xml->writeElement('Street', $member['street']);
    $xml->writeElement('Number', $member['number']);
    $xml->writeElement('Email', $member['email']);
    $xml->writeElement('MobilePrefix', $member['mobileprefix']);
    $xml->writeElement('MobileNumber', $member['mobilenumber']);
    $xml->writeElement('Postalcode', $member['postalcode']);
    $xml->writeElement('PreferredLanguage', $member['language']);
    $xml->writeElement('Title', $member['title']);
  $xml->endElement();
  $xml = $xml->outputMemory();

  $options = array(
    'method' => 'POST',
    'data' => $xml,
    'timeout' => 60,
    'headers' => array(
      'Content-Type' => 'text/xml; charset=utf-8',
    ),
  );
  if (!empty($commerce_bpost_settings['account']['bpack_user']) && !empty($commerce_bpost_settings['account']['bpack_passkey'])) {
    $options['headers']['Authorization'] = 'Basic ' . base64_encode($commerce_bpost_settings['account']['bpack_user'] . ':' . $commerce_bpost_settings['account']['bpack_passkey']);
  }
  watchdog('commerce_bpost', 'Webservice > create_bpack_member method: request sent for client !back_mail.', array('!bpack_mail' => $member['email']));
  $response = commerce_bpost_request_bpost('customer', $options, 'http://www.bpack247.be/BpostRegistrationWebserviceREST/servicecontroller.svc/');
  watchdog('commerce_bpost', 'Webservice > create_bpack_member method: reply with code !code.', array('!code' => $response->code));
  if ($response->code == 200) {
    return json_decode(json_encode((array) simplexml_load_string($response->data)), 1);
  }
  else {
    $error = NULL;
    if (isset($response->data)) {
      $xml = simplexml_load_string($response->data);
      $message = (string) $xml->Message;
      $error = $message;
    }
    return array('error' => $error);
  }
}

function commerce_bpost_get_point_details($id, $type) {
  $responsetoarray = array();
  global $language;
  $get = 'Function=info';
  $get .= '&Partner=999998';
  $get .= '&AddId=A001';
  $get .= '&Id=' . $id;
  $get .= '&Type=' . $type;
  // Language.
  $get .= '&Language=';
  if ($language->language == "FR" || $language->language == "NL") {
    $get .= $language->language;
  }
  else {
    $get .= 'NL';
  }
  $options = array(
    'method' => 'GET',
    'headers' => array(
      'Content-Type' => 'text/xml; charset=utf-8',
    ),
  );
  watchdog('commerce_bpost', 'Webservice > get_point_details method: request sent for point !point_id.', array('!point_id' => $id));
  $response = commerce_bpost_request_bpost($get, $options, 'http://taxipost.geo6.be/Locator?');
  watchdog('commerce_bpost', 'Webservice > get_point_details method: reply with code !code.', array('!code' => $response->code));
  if ($response->code == 200) {
    $responsetoarray = json_decode(json_encode((array) simplexml_load_string($response->data)), 1);
  }
  return $responsetoarray;
}

/**
 * Get the bpost label for a specific order.
 *
 * @param $order_id
 *  The order we want to get the label from.
 *
 * @return bool
 */
function commerce_bpost_create_label($order, $entity_type = 'commerce_order') {
  $order_wrapper = entity_metadata_wrapper($entity_type, $order);
  $order_id = $order_wrapper->getIdentifier();
  $bpost_id = _commerce_bpost_get_bpost_id($order);
  $commerce_bpost_settings = variable_get('commerce_bpost_settings');
  $get = "/" . $commerce_bpost_settings['account']['account_id'] . "/orders/" . $bpost_id . "/labels/" . $commerce_bpost_settings['label']['format'];
  if (isset($commerce_bpost_settings['label']['return']) && $commerce_bpost_settings['label']['return'] == 'include') {
    $get .= '/withReturnLabels';
  }
  $options = array(
    'method' => 'GET',
    'headers' => array(
      'Accept' => 'application/vnd.bpost.shm-label-pdf-v3+XML',
    ),
  );
  $authorization = isset($commerce_bpost_settings['account']['account_id']) ? $commerce_bpost_settings['account']['account_id'] : '';
  $authorization .= ':';
  $authorization .= isset($commerce_bpost_settings['account']['passphrase']) ? $commerce_bpost_settings['account']['passphrase'] : '';
  $options['headers'] += array('Authorization' => 'Basic ' . base64_encode($authorization));

  watchdog('commerce_bpost', 'Webservice > createLabel method: request for order n°!order_id.', array('!order_id' => $order_id));
  $response = commerce_bpost_request_bpost($get, $options, 'https://api.bpost.be/services/shm');
  watchdog('commerce_bpost', 'Webservice > createLabel method: reply with code !code.', array('!code' => $response->code));

  $barcode_success = FALSE;
  $file_success = FALSE;
  if ($response->code == 200) {
    $data = simplexml_load_string($response->data);

    $barcodes = $order_wrapper->field_barcode->value();
    $labels = $order_wrapper->field_bpost_label->value();
    foreach ($data->label as $label) {
      // Barcode
      if (isset($label->barcode)) {
        foreach ($label->barcode as $barcode) {
          $barcodes[] = (string) $barcode;
        }
        $barcode_success = TRUE;
      }
      // Label
      if (isset($label->bytes)) {
        $file_path = 'private://bpost_labels';
        $file_name = 'label_order_' . $order_id . '.pdf';
        if (file_prepare_directory($file_path, FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS) ) {
          $file_content_64 = (string) $label->bytes;
          $file = file_save_data(base64_decode($file_content_64), $file_path . '/' . $file_name);
          if (isset($file->fid)) {
            $file->display = 0;
            $labels[] = (array) $file;
            $order->status = 'bpost_printed';
            $file_success = TRUE;
          }
        }
      }
    }
    $order_wrapper->field_barcode->set($barcodes);
    $order_wrapper->field_bpost_label->set($labels);
  }
  return $barcode_success || $file_success;
}

/**
 * Generate bpost tracking urls for a specific order.
 *
 * @param $order_id
 *  The order we want to generate tracking urls for.
 *
 * @return string|null
 */
function commerce_bpost_get_order_tracking_urls($order_id, $entity_type = 'commerce_order') {
  $order_wrapper = entity_metadata_wrapper($entity_type, $order_id);
  $barrcodes = $order_wrapper->field_barcode->value();

  $output = NULL;

  // Return barcodes finish by one of this codes.
  $return_barcodes = array(
    '050' => '050',
    '051' => '051',
    '125' => '125',
    '134' => '134',
  );

  foreach ($barrcodes as $barrcode) {
    // Do not output return barcodes.
    if (!isset($return_barcodes[substr($barrcode, -3)])) {
      $output .= commerce_bpost_get_tracking_url($barrcode) . '<br />';
    }
  }

  return $output;
}

/**
 * Generate tracking url for a specific barrcode.
 *
 * @param $barrcode
 *   Barrcode to generate url for.
 *
 * @return string
 *   Formated tracking url using l()
 */
function commerce_bpost_get_tracking_url($barrcode) {
  $query = drupal_http_build_query(array(
    'searchByItemCode' => 'true',
    'itemCodes' => $barrcode,
    'oss_language' => 'en',
  ));

  $url = 'http://track.bpost.be/etr/light/performSearch.do?' . $query;
  return t('Parcel n°') . l($barrcode, $url, array('external' => TRUE, 'attributes' => array('target' => '_blank')));
}

/**
 * Get Shop info.
 */
function commerce_bpost_get_shop_info() {
  if ($data = cache_get('commerce_bpost_shopinfo')) {
    $data = simplexml_load_string($data->data);
  }
  else {
    $commerce_bpost_settings = variable_get('commerce_bpost_settings');
    watchdog('commerce_bpost', 'Webservice > getShopInfo method');
    $response = commerce_bpost_request_bpost($commerce_bpost_settings['account']['account_id'] . '/productconfig', array('Accept' => 'application/vnd.bpost.shm-productConfiguration-v3+XML'));
    watchdog('commerce_bpost', 'Webservice > getShopInfo method: reply with code !code.', array('!code' => $response->code));
    if ($response->code == 200) {
      $data = simplexml_load_string($response->data);
      cache_set('commerce_bpost_shopinfo', $response->data, 'cache', strtotime('now +1 hour'));
    }
    else {
      $data = FALSE;
    }
  }
  return $data;
}

/**
 * Return the bpost shipping product for a given service and country.
 *
 * @param string $service
 *  Shipping service machine name (Drupal side).
 * @param $country
 *  The user shipping address country.
 * @param bool $return
 *  Whether its a return or not.
 *
 * @return string
 *  The bpost shipping product
 */
function commerce_bpost_get_shipping_product($service, $country, $return = FALSE) {
  $commerce_bpost_settings = variable_get('commerce_bpost_settings');
  $international = !empty($commerce_bpost_settings['options']['international_delivery']) ? $commerce_bpost_settings['options']['international_delivery'] : 'bpack World Business';
  $default_shipping_products = array(
    'delivery' => array(
      'bpost_home'                 => 'bpack 24h Pro',
      'bpost_bpack'                => 'bpack 24h Pro',
      'bpost_postoffice_postpoint' => 'bpack@bpost',
      'bpost_world'                => $international,
    ),
    'return' => array(
      'bpost_home'                 => 'bpack Easy Retour',
      'bpost_bpack'                => 'bpack Easy Retour',
      'bpost_postoffice_postpoint' => 'bpack Easy Retour',
      'bpost_world'                => 'bpack World Easy Return',
    )
  );
  $shipping_product = NULL;
  $shipping_product_key = $return ? 'return': 'delivery';
  if (!$return) {
    $data = commerce_bpost_get_shop_info();
    $matching_products = array();
    if (!empty($data)) {
      $mapping_services = array(
        'bpost_bpack' => 'Parcel machine',
        'bpost_postoffice_postpoint' => 'pick-up point',
        'bpost_home' => 'home or office',
        'bpost_world' => 'home or office',
      );
      foreach ($data->deliveryMethod as $deliveryMethod) {
        foreach ($deliveryMethod->attributes() as $key => $value) {
          if (!($key == "name" && ((string) $value) == $mapping_services[$service])) {
            continue 2;
          }
        }
        foreach ($deliveryMethod->product as $product) {
          foreach ($product->attributes() as $key => $value) {
            if ($key == "name") {
              $matching_product = (string) $value;
              break;
            }
          }
          if (!empty($matching_product)) {
            foreach ($product->price as $price) {
              foreach ($price->attributes() as $key => $value) {
                if ($key == "countryIso2Code" && ((string) $value == $country)) {
                  $matching_products[] = $matching_product;
                }
              }
            }
          }
        }
      }
    }
    $matching_products = array_diff($matching_products, $default_shipping_products['return']);
    if (!empty($matching_products)) {
      if ($value = array_intersect($matching_products, $default_shipping_products[$shipping_product_key])) {
        $shipping_product = reset($value);
      }
      else {
        $shipping_product = reset($matching_products);
      }
    }
  }
  if (empty($shipping_product)) {
    $shipping_product = $default_shipping_products[$shipping_product_key][$service];
  }

  return $shipping_product;
}

/**
 * Get bpost order id.
 *
 * @param $order
 *   Order to generate bpost id for
 *
 * @return string
 *   Generated bpost order id
 */
function _commerce_bpost_get_bpost_id($order) {
  if (!empty($order->data['bpost_id'])) {
    return $order->data['bpost_id'];
  }

  return 'DRU_1_' . $order->order_id;
}

/**
 * Set id provided by bpost in the order
 *
 * @param $order
 *   Order to set the id for
 * @param $bpost_id
 *   Id to be setted
 */
function _commerce_bpost_set_bpost_id(&$order, $bpost_id) {
  $order->data['bpost_id'] = $bpost_id;
}