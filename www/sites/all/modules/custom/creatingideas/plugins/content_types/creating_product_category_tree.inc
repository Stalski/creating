<?php

$plugin = array(
  'title' => t('Content pane for product category tree'),
  'single' => TRUE,
  'title' => t('Creating Product Category Tree'),
  'icon' => 'icon_contact.png',
  'description' => t('Custom widgets for the Creating website.'),
  'category' => t('Creating Widgets'),
);


/**
 * Render a block with all main taxonomy vocabulary lists.
 */
function creatingideas_creating_product_category_tree_content_type_render($subtype, $conf, $panel_args, $context) {

  // Build the content type block.
  $block = new stdClass();
  $block->module  = 'creatingideas';
  $block->delta   = 'tree';
  $block->title   = t('Creating Product Category Tree');

  $vocabularies = array(
    'brand' => 'brand',
    'cloth_type' => 'cloth_type',
    'cloth_theme' => 'cloth_style',
    'color' => 'color'
  );
  $items = array();

  foreach ($vocabularies as $vocabulary_name => $vocabulary_field) {

    $query = db_select('taxonomy_term_data', 'td');
    $query->innerJoin("taxonomy_vocabulary", "tv", "tv.vid = td.vid");
    $query->fields('td', array('tid', 'name'));
    $query->addField('tv', 'name', 'voc_name');

    $query->innerJoin("field_data_field_" . $vocabulary_field, "f1", "f1.entity_type = 'commerce_product' AND f1.bundle = 'cloth' AND f1.field_" . $vocabulary_field . "_target_id = td.tid ");
    $query->innerJoin("field_data_field_products", "fp1", "fp1.entity_type = 'node' AND fp1.bundle = 'cloth_display' AND fp1.field_products_product_id = f1.entity_id ");
    $query->addExpression('COUNT(f1.entity_id)', 'num_products');
    if (drupal_is_front_page()) {
      $query->condition('tv.machine_name', array('brand', 'cloth_type'), 'IN');
    }
    $query->groupBy('td.tid');

    $query->condition('tv.machine_name', $vocabulary_name, '=');
    $result = $query->execute();

    foreach ($result as $row) {
      $term = taxonomy_term_load($row->tid);
      if (!empty($row->num_products)) {
        $term->num_products = $row->num_products;
      }
      $items[$row->voc_name][] = $term;
    }

  }

  if (!empty($items)) {
    $block->content = array(
      '#theme' => 'creatingideas_product_category_tree',
      '#items' => $items,
    );
  }

  return $block;

}

/**
 * Returns an edit form for custom type settings.
 */
function creatingideas_creating_product_category_tree_content_type_edit_form($form, &$form_state) {
  // Empty so that we can have title override.
  return $form;
}

/**
 * Submit handler for Creating Product Category Tree settings.
 */
function creatingideas_creating_product_category_tree_content_type_edit_form_submit($form, &$form_state) {

}

/**
 * Returns the administrative title for a type.
 */
function creatingideas_creating_product_category_tree_content_type_admin_title($subtype, $conf, $context) {
  return t('Creating Product Category Tree');
}

