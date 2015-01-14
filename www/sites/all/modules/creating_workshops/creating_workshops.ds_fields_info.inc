<?php

/**
 * @file
 * Extra ds fields for creating ideas.
 *
 */

/**
 * Implements hook_ds_fields_info().
 */
function creating_workshops_ds_fields_info($entity_type) {

  $fields = array();
  $file = drupal_get_path('module', 'creating_workshops') . '/includes/ds.inc';

  $fields['node']['appointment_only'] = array(
    'title' => t('Appointment only (if no date)'),
    'field_type' => DS_FIELD_TYPE_FUNCTION,
    'function' => 'creating_workshops_render_appointment_only',
    'ui_limit' => array('workshop|calendar'),
    'file' => $file,
  );
  $fields['node']['title_pictures'] = array(
    'title' => t('Title: Enkele foto\'s van werkjes'),
    'field_type' => DS_FIELD_TYPE_FUNCTION,
    'function' => 'creating_workshops_render_title_pictures',
    'ui_limit' => array('workshop|*'),
    'file' => $file,
  );

  if (!isset($fields[$entity_type])) {
    return;
  }

  return array($entity_type => $fields[$entity_type]);
}