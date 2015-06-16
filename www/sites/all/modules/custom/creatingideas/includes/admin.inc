<?php

/**
 * @file
 * Administration file for settings specific to Creating.
 */


/**
 * Page callback to render a settings form for social configuration.
 */
function creatingideas_social_settings() {

  $form = array();

  $form['social'] = array(
    '#title' => 'Social media instellingen',
    '#type' => 'fieldset',
  );

  $form['social']['creating_facebook_url'] = array(
    '#type' => 'textfield',
    '#title' => 'Facebook url',
    '#description' => 'Relevant voor de aankoop van stoffen.',
    '#default_value' => variable_get('creating_facebook_url', 'https://www.facebook.com/creatingideas.be'),
  );

  $form['social']['creating_facebook_optional_url'] = array(
    '#type' => 'textfield',
    '#title' => 'Facebook optionele url',
    '#description' => 'Voor de organisatie en planning en communicatie voor mensen die naar de workshops komen.',
    '#default_value' => variable_get('creating_facebook_optional_url', 'https://www.facebook.com/creating.workshops'),
  );

  $form['social']['creating_twitter_url'] = array(
    '#type' => 'textfield',
    '#title' => 'Twitter account url',
    '#description' => 'Algemene twitter account.',
    '#default_value' => variable_get('creating_facebook_optional_url', ''),
  );

  return system_settings_form($form);

}


/**
 * Page callback to render a settings form for webshop configuration.
 */
function creatingideas_webshop_settings() {

  $form = array();

  $form['delivery'] = array(
    '#title' => 'Verzending',
    '#type' => 'fieldset',
  );

  $form['delivery']['creating_simple_post_flat_rate'] = array(
    '#type' => 'textfield',
    '#title' => 'Rate for the simple delivery by post',
    '#description' => 'This will be used as the amount for the custom rates for simple deliveries by (b)post.',
    '#default_value' => variable_get('creating_simple_post_flat_rate', 250),
  );

  $form['order_summary'] = array(
    '#title' => 'Verzending',
    '#type' => 'fieldset',
  );

  $creating_order_summary_text = variable_get('creating_order_summary_text', array(
    'value' => '',
    'format' => filter_default_format(),
  ));
  $form['order_summary']['creating_order_summary_text'] = array(
    '#type' => 'text_format',
    '#title' => 'Tekst bij bestellingsoverzicht (laatste stap)',
    '#description' => 'Tekst bij het bestellingsoverzicht bij de laatste bestel stap.',
    '#default_value' => $creating_order_summary_text['value'],
    '#format' => $creating_order_summary_text['format'],
  );

  $creating_order_submitted_text = variable_get('creating_order_submitted_text', array(
    'value' => '',
    'format' => filter_default_format(),
  ));
  $form['order_summary']['creating_order_submitted_text'] = array(
    '#type' => 'text_format',
    '#title' => 'Tekst bij bestellingsoverzicht (na bestellen)',
    '#description' => 'Tekst bij het bestellingsoverzicht na afronden van de bestelling.',
    '#default_value' => $creating_order_submitted_text['value'],
    '#format' => $creating_order_submitted_text['format'],
  );

  $creating_order_mail_text = variable_get('creating_order_mail_text', array(
    'value' => '',
    'format' => filter_default_format(),
  ));
  $form['order_summary']['creating_order_mail_text'] = array(
    '#type' => 'text_format',
    '#title' => 'Tekst bij bestellingsoverzicht (mail)',
    '#description' => 'Tekst bij het bestellingsoverzicht bij de mail na afronden van de bestelling.',
    '#default_value' => $creating_order_mail_text['value'],
    '#format' => $creating_order_mail_text['format'],
  );

  return system_settings_form($form);

}

/**
 * Page callback to render a contact settings form.
 */
function creatingideas_contact_settings() {

  $form = array();

  $form['shop'] = array(
    '#title' => 'Workshops',
    '#type' => 'fieldset',
  );

  $creating_shop_address_text = variable_get('creating_shop_address', array(
    'value' => '',
    'format' => filter_default_format(),
  ));
  $form['shop']['creating_shop_address'] = array(
    '#type' => 'text_format',
    '#title' => 'Adres van winkel en workshop',
    '#rows' => 4,
    '#description' => 'Adres informatie bij de betalingsweergave.',
    '#default_value' => $creating_shop_address_text['value'],
    '#format' => $creating_shop_address_text['format'],
  );

  $form['company'] = array(
    '#title' => 'Bedrijf',
    '#type' => 'fieldset',
  );

  $creating_company_address_text = variable_get('creating_company_address', array(
    'value' => '',
    'format' => filter_default_format(),
  ));
  $form['company']['creating_company_address'] = array(
    '#type' => 'text_format',
    '#title' => 'Adres van het bedrijf',
    '#rows' => 4,
    '#description' => 'Adres gekend door officiële instanties.',
    '#default_value' => $creating_company_address_text['value'],
    '#format' => $creating_company_address_text['format'],
  );

  return system_settings_form($form);

}


/**
 * Page callback to render a global settings form.
 */
function creatingideas_global_settings() {

  $form = array();



  return system_settings_form($form);

}
