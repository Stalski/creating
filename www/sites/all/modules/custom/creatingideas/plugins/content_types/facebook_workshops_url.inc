<?php

$plugin = array(
  'title' => t('Content pane for facebook workshops url'),
  'single' => TRUE,
  'title' => t('Creating facebook workshops url'),
  'category' => t('Creating Widgets'),
);


/**
 * Render a block with all main taxonomy vocabulary lists.
 */
function creatingideas_facebook_workshops_url_content_type_render($subtype, $conf, $panel_args, $context) {

  // Build the content type block.
  $block = new stdClass();
  $block->module  = 'creatingideas';
  $block->delta   = 'tree';
  $block->title   = '';

  $block->content = array(
    '#type' => 'markup',
    '#markup' => l(t('Our workshops on Facebook'), variable_get('creating_facebook_url', 'https://www.facebook.com/creatingideas.be'),
      array('absolute' => TRUE)),
  );

  return $block;

}

/**
 * Returns an edit form for custom type settings.
 */
function creatingideas_facebook_workshops_url_content_type_edit_form($form, &$form_state) {
  // Empty so that we can have title override.
  return $form;
}

/**
 * Submit handler for facebook_workshops_url settings.
 */
function creatingideas_facebook_workshops_url_content_type_edit_form_submit($form, &$form_state) {

}

/**
 * Returns the administrative title for a type.
 */
function creatingideas_facebook_workshops_url_content_type_admin_title($subtype, $conf, $context) {
  return t('Creating Product Category Tree');
}

