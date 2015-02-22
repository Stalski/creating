<?php
/**
 * @file
 * featured_page.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function featured_page_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_featured_page|node|featured_page|form';
  $field_group->group_name = 'group_featured_page';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'featured_page';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_horizontals';
  $field_group->data = array(
    'label' => 'Featured page',
    'weight' => '10',
    'children' => array(
      0 => 'field_small_image',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-featured-page field-group-htab',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $export['group_featured_page|node|featured_page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_general|node|featured_page|form';
  $field_group->group_name = 'group_general';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'featured_page';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_horizontals';
  $field_group->data = array(
    'label' => 'General info',
    'weight' => '9',
    'children' => array(
      0 => 'body',
      1 => 'field_page_type',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-general field-group-htab',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $export['group_general|node|featured_page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_header_info|node|featured_page|form';
  $field_group->group_name = 'group_header_info';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'featured_page';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_horizontals';
  $field_group->data = array(
    'label' => 'Header information',
    'weight' => '11',
    'children' => array(
      0 => 'field_bg_image',
      1 => 'field_link',
      2 => 'field_header_text',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-header-info field-group-htab',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $export['group_header_info|node|featured_page|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_horizontals|node|featured_page|form';
  $field_group->group_name = 'group_horizontals';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'featured_page';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Horizontal group',
    'weight' => '1',
    'children' => array(
      0 => 'group_featured_page',
      1 => 'group_general',
      2 => 'group_header_info',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => 'group-horizontals field-group-htabs',
      ),
    ),
  );
  $export['group_horizontals|node|featured_page|form'] = $field_group;

  return $export;
}
