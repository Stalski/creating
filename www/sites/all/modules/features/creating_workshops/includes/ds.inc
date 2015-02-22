<?php

/**
 * @file
 * Display suite fields.
 */

/**
 * Render the date as "appointment only"
 * @param array $field
 * @return string
 */
function creating_workshops_render_appointment_only($field) {
  $entity = $field['entity'];

  if (!empty($entity->field_calendar)) {
    return;
  }

  return '<div class="calendar-list">
    <div class="calendar-item">Deze workshop is enkel ' . l('op afspraak', 'contact',
        array('attributes' => array('class' => array('button')))) . '</div></div>';
}

/**
 * Render the title in a custom way to guide picture/gallery.
 * @param array $field
 */
function creating_workshops_render_title_pictures($field) {

  $entity = $field['entity'];

  return 'Enkele foto\'s van de werkjes uit de lessen "' . check_plain($entity->title) . '"';
}
