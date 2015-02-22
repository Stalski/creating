<?php
/**
 * @file
 * featured_page.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function featured_page_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function featured_page_node_info() {
  $items = array(
    'featured_page' => array(
      'name' => t('Featured page'),
      'base' => 'node_content',
      'description' => t('Create a featured page when you want to create a page with the ability to make it available in the header slideshow. This way you can create hot topics for a certain period of time.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
