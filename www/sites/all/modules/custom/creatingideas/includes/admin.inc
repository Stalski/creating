<?php

/**
 * @file
 * Administration file for settings specific to Creating.
 */

/**
 * Page callback to render a global settings form.
 */
function creatingideas_global_settings() {

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

  $form['webshop'] = array(
    '#title' => 'Webshop instellingen',
    '#type' => 'fieldset',
  );
  $form['webshop']['creating_contact_company_address'] = array(
    '#type' => 'textarea',
    '#title' => 'Facebook optionele url',
    '#rows' => 4,
    '#description' => 'Adres informatie bij de betalingsweergave.',
    '#default_value' => variable_get('creating_contact_company_address', ''),
  );

  $form['webshop']['creating_simple_post_flat_rate'] = array(
    '#type' => 'textfield',
    '#title' => 'Rate for the simple delivery by post',
    '#description' => 'This will be used as the amount for the custom rates for simple deliveries by (b)post.',
    '#default_value' => variable_get('creating_simple_post_flat_rate', 250),
  );

  return system_settings_form($form);

}
