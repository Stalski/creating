<?php
/**
 * @file
 * creating_webshop.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function creating_webshop_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_general|commerce_product|cloth|form';
  $field_group->group_name = 'group_general';
  $field_group->entity_type = 'commerce_product';
  $field_group->bundle = 'cloth';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_horizontals';
  $field_group->data = array(
    'label' => 'General info',
    'weight' => '40',
    'children' => array(
      0 => 'field_extra_info',
      1 => 'field_brand',
      2 => 'commerce_stock',
      3 => 'field_color',
      4 => 'field_cloth_type',
      5 => 'field_cloth_style',
      6 => 'sku',
      7 => 'title',
      8 => 'status',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'General info',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-general field-group-htab',
        'description' => '',
      ),
      'formatter' => 'open',
    ),
  );
  $export['group_general|commerce_product|cloth|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_general|commerce_product|sewing_kit|form';
  $field_group->group_name = 'group_general';
  $field_group->entity_type = 'commerce_product';
  $field_group->bundle = 'sewing_kit';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_horizontals';
  $field_group->data = array(
    'label' => 'General info',
    'weight' => '38',
    'children' => array(
      0 => 'field_extra_info',
      1 => 'sku',
      2 => 'title',
      3 => 'status',
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
  $export['group_general|commerce_product|sewing_kit|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_horizontals|commerce_product|cloth|form';
  $field_group->group_name = 'group_horizontals';
  $field_group->entity_type = 'commerce_product';
  $field_group->bundle = 'cloth';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Horizontal group',
    'weight' => '6',
    'children' => array(
      0 => 'group_pricing',
      1 => 'group_media',
      2 => 'group_general',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => 'group-horizontals field-group-htabs',
      ),
    ),
  );
  $export['group_horizontals|commerce_product|cloth|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_horizontals|commerce_product|sewing_kit|form';
  $field_group->group_name = 'group_horizontals';
  $field_group->entity_type = 'commerce_product';
  $field_group->bundle = 'sewing_kit';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Horizontal group',
    'weight' => '1',
    'children' => array(
      0 => 'group_general',
      1 => 'group_pricing',
      2 => 'group_media',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => 'group-horizontals field-group-htabs',
      ),
    ),
  );
  $export['group_horizontals|commerce_product|sewing_kit|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_media|commerce_product|cloth|form';
  $field_group->group_name = 'group_media';
  $field_group->entity_type = 'commerce_product';
  $field_group->bundle = 'cloth';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_horizontals';
  $field_group->data = array(
    'label' => 'Media',
    'weight' => '42',
    'children' => array(
      0 => 'field_leading_image',
      1 => 'field_more_images',
      2 => 'field_bg_image',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-media field-group-htab',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $export['group_media|commerce_product|cloth|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_media|commerce_product|sewing_kit|form';
  $field_group->group_name = 'group_media';
  $field_group->entity_type = 'commerce_product';
  $field_group->bundle = 'sewing_kit';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_horizontals';
  $field_group->data = array(
    'label' => 'Media',
    'weight' => '41',
    'children' => array(
      0 => 'field_leading_image',
      1 => 'field_more_images',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-media field-group-htab',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $export['group_media|commerce_product|sewing_kit|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_pricing|commerce_product|cloth|form';
  $field_group->group_name = 'group_pricing';
  $field_group->entity_type = 'commerce_product';
  $field_group->bundle = 'cloth';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_horizontals';
  $field_group->data = array(
    'label' => 'Dimensions & Pricing',
    'weight' => '41',
    'children' => array(
      0 => 'commerce_price',
      1 => 'field_weight',
      2 => 'field_dimensions',
      3 => 'field_price_per_meter',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'label' => 'Dimensions & Pricing',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-pricing field-group-htab',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $export['group_pricing|commerce_product|cloth|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_pricing|commerce_product|sewing_kit|form';
  $field_group->group_name = 'group_pricing';
  $field_group->entity_type = 'commerce_product';
  $field_group->bundle = 'sewing_kit';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_horizontals';
  $field_group->data = array(
    'label' => 'Pricing',
    'weight' => '40',
    'children' => array(
      0 => 'commerce_price',
      1 => 'field_weight',
      2 => 'commerce_stock',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-pricing field-group-htab',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $export['group_pricing|commerce_product|sewing_kit|form'] = $field_group;

  return $export;
}
