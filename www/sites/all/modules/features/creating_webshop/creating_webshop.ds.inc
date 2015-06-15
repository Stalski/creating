<?php
/**
 * @file
 * creating_webshop.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function creating_webshop_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'commerce_product|cloth|node_full';
  $ds_fieldsetting->entity_type = 'commerce_product';
  $ds_fieldsetting->bundle = 'cloth';
  $ds_fieldsetting->view_mode = 'node_full';
  $ds_fieldsetting->settings = array(
    'commerce_price' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'fi' => TRUE,
          'fi-el' => 'div',
          'fi-cl' => 'teaser-price',
          'fi-at' => '',
          'fi-def-at' => FALSE,
          'fi-odd-even' => FALSE,
        ),
      ),
    ),
    'field_dimensions' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb' => 'Afmetingen',
          'fi' => TRUE,
          'fi-el' => 'div',
          'fi-cl' => '',
          'fi-at' => '',
          'fi-def-at' => FALSE,
          'fi-odd-even' => FALSE,
        ),
      ),
    ),
    'field_brand' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'ow' => TRUE,
          'ow-el' => 'span',
          'ow-cl' => 'category',
          'ow-def-cl' => FALSE,
          'ow-at' => '',
          'ow-def-at' => FALSE,
          'fi' => TRUE,
          'fi-el' => 'span',
          'fi-cl' => 'label label-default',
          'fi-at' => '',
          'fi-def-at' => FALSE,
          'fi-odd-even' => FALSE,
        ),
      ),
    ),
    'field_price_per_meter' => array(
      'formatter_settings' => array(
        'ft' => array(
          'lb' => 'Prijs per meter ',
        ),
      ),
    ),
    'commerce_stock' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'lb' => 'In voorraad',
          'fi' => TRUE,
          'fi-el' => 'span',
          'fi-cl' => '',
          'fi-at' => '',
          'fi-def-at' => FALSE,
          'fi-odd-even' => FALSE,
        ),
      ),
    ),
    'field_color' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'ow' => TRUE,
          'ow-el' => 'span',
          'ow-cl' => 'category',
          'ow-def-cl' => FALSE,
          'ow-at' => '',
          'ow-def-at' => FALSE,
          'fi' => TRUE,
          'fi-el' => 'span',
          'fi-cl' => 'label label-default',
          'fi-at' => '',
          'fi-def-at' => FALSE,
          'fi-odd-even' => FALSE,
        ),
      ),
    ),
    'field_cloth_type' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'ow' => TRUE,
          'ow-el' => 'span',
          'ow-cl' => 'category',
          'ow-def-cl' => FALSE,
          'ow-at' => '',
          'ow-def-at' => FALSE,
          'fi' => TRUE,
          'fi-el' => 'span',
          'fi-cl' => 'label label-default',
          'fi-at' => '',
          'fi-def-at' => FALSE,
          'fi-odd-even' => FALSE,
        ),
      ),
    ),
    'field_cloth_style' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'ow' => TRUE,
          'ow-el' => 'span',
          'ow-cl' => 'category',
          'ow-def-cl' => FALSE,
          'ow-at' => '',
          'ow-def-at' => FALSE,
          'fi' => TRUE,
          'fi-el' => 'span',
          'fi-cl' => 'label label-default',
          'fi-at' => '',
          'fi-def-at' => FALSE,
          'fi-odd-even' => FALSE,
        ),
      ),
    ),
  );
  $export['commerce_product|cloth|node_full'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'commerce_product|cloth|node_teaser';
  $ds_fieldsetting->entity_type = 'commerce_product';
  $ds_fieldsetting->bundle = 'cloth';
  $ds_fieldsetting->view_mode = 'node_teaser';
  $ds_fieldsetting->settings = array(
    'commerce_price' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'fi' => TRUE,
          'fi-el' => 'div',
          'fi-cl' => 'teaser-price',
          'fi-at' => '',
          'fi-def-at' => FALSE,
          'fi-odd-even' => FALSE,
        ),
      ),
    ),
  );
  $export['commerce_product|cloth|node_teaser'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'commerce_product|sewing_kit|node_full';
  $ds_fieldsetting->entity_type = 'commerce_product';
  $ds_fieldsetting->bundle = 'sewing_kit';
  $ds_fieldsetting->view_mode = 'node_full';
  $ds_fieldsetting->settings = array(
    'commerce_price' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'fi' => TRUE,
          'fi-el' => 'div',
          'fi-cl' => 'teaser-price',
          'fi-at' => '',
          'fi-def-at' => FALSE,
          'fi-odd-even' => FALSE,
        ),
      ),
    ),
    'field_more_images' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'ow' => TRUE,
          'ow-el' => 'div',
          'ow-cl' => 'row',
          'ow-def-cl' => FALSE,
          'ow-at' => '',
          'ow-def-at' => FALSE,
          'fi' => TRUE,
          'fi-el' => 'div',
          'fi-cl' => 'col-xs-6 col-md-3',
          'fi-at' => '',
          'fi-def-at' => FALSE,
          'fi-odd-even' => FALSE,
        ),
      ),
    ),
  );
  $export['commerce_product|sewing_kit|node_full'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'commerce_product|sewing_kit|node_teaser';
  $ds_fieldsetting->entity_type = 'commerce_product';
  $ds_fieldsetting->bundle = 'sewing_kit';
  $ds_fieldsetting->view_mode = 'node_teaser';
  $ds_fieldsetting->settings = array(
    'commerce_price' => array(
      'formatter_settings' => array(
        'ft' => array(
          'func' => 'theme_ds_field_expert',
          'fi' => TRUE,
          'fi-el' => 'div',
          'fi-cl' => 'teaser-price',
          'fi-at' => '',
          'fi-def-at' => FALSE,
          'fi-odd-even' => FALSE,
        ),
      ),
    ),
    'field_leading_image' => array(
      'formatter_settings' => array(
        'ft' => array(),
      ),
    ),
  );
  $export['commerce_product|sewing_kit|node_teaser'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|cloth_display|full';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'cloth_display';
  $ds_fieldsetting->view_mode = 'full';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link' => '0',
        'wrapper' => 'h1',
        'class' => '',
        'ft' => array(),
      ),
    ),
    'links' => array(
      'weight' => '12',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|cloth_display|full'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|cloth_display|teaser';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'cloth_display';
  $ds_fieldsetting->view_mode = 'teaser';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link' => '1',
        'wrapper' => 'h2',
        'class' => 'media-title',
        'ft' => array(),
      ),
    ),
    'field_products' => array(
      'formatter_settings' => array(
        'ft' => array(),
      ),
    ),
  );
  $export['node|cloth_display|teaser'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|sewing_kit_display|full';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'sewing_kit_display';
  $ds_fieldsetting->view_mode = 'full';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link' => '0',
        'wrapper' => 'h1',
        'class' => '',
        'ft' => array(),
      ),
    ),
    'links' => array(
      'weight' => '6',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|sewing_kit_display|full'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|sewing_kit_display|teaser';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'sewing_kit_display';
  $ds_fieldsetting->view_mode = 'teaser';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link' => '1',
        'wrapper' => 'h2',
        'class' => 'media-title',
        'ft' => array(),
      ),
    ),
  );
  $export['node|sewing_kit_display|teaser'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|voucher_display|teaser';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'voucher_display';
  $ds_fieldsetting->view_mode = 'teaser';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'field_products' => array(
      'formatter_settings' => array(
        'ft' => array(),
      ),
    ),
  );
  $export['node|voucher_display|teaser'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function creating_webshop_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'commerce_product|cloth|node_full';
  $ds_layout->entity_type = 'commerce_product';
  $ds_layout->bundle = 'cloth';
  $ds_layout->view_mode = 'node_full';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
        1 => 'commerce_price',
        2 => 'field_dimensions',
        3 => 'field_extra_info',
        4 => 'field_brand',
        5 => 'field_cloth_style',
        6 => 'field_cloth_type',
        7 => 'field_color',
        8 => 'field_price_per_meter',
        9 => 'commerce_stock',
        10 => 'field_leading_image',
        11 => 'field_more_images',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'commerce_price' => 'ds_content',
      'field_dimensions' => 'ds_content',
      'field_extra_info' => 'ds_content',
      'field_brand' => 'ds_content',
      'field_cloth_style' => 'ds_content',
      'field_cloth_type' => 'ds_content',
      'field_color' => 'ds_content',
      'field_price_per_meter' => 'ds_content',
      'commerce_stock' => 'ds_content',
      'field_leading_image' => 'ds_content',
      'field_more_images' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['commerce_product|cloth|node_full'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'commerce_product|cloth|node_teaser';
  $ds_layout->entity_type = 'commerce_product';
  $ds_layout->bundle = 'cloth';
  $ds_layout->view_mode = 'node_teaser';
  $ds_layout->layout = 'panels-onecol';
  $ds_layout->settings = array(
    'regions' => array(
      'middle' => array(
        0 => 'title',
        1 => 'field_dimensions',
        2 => 'field_leading_image',
      ),
    ),
    'fields' => array(
      'title' => 'middle',
      'field_dimensions' => 'middle',
      'field_leading_image' => 'middle',
    ),
    'classes' => array(),
    'wrappers' => array(
      'middle' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['commerce_product|cloth|node_teaser'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'commerce_product|cloth|teaser';
  $ds_layout->entity_type = 'commerce_product';
  $ds_layout->bundle = 'cloth';
  $ds_layout->view_mode = 'teaser';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
        1 => 'commerce_price',
        2 => 'field_brand',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'commerce_price' => 'ds_content',
      'field_brand' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['commerce_product|cloth|teaser'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'commerce_product|sewing_kit|default';
  $ds_layout->entity_type = 'commerce_product';
  $ds_layout->bundle = 'sewing_kit';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'panels-bootstrap_thumbnail';
  $ds_layout->settings = array(
    'regions' => array(
      'thumbnail_image' => array(
        0 => 'field_leading_image',
      ),
      'caption' => array(
        1 => 'title',
        2 => 'field_extra_info',
        3 => 'commerce_price',
      ),
    ),
    'fields' => array(
      'field_leading_image' => 'thumbnail_image',
      'title' => 'caption',
      'field_extra_info' => 'caption',
      'commerce_price' => 'caption',
    ),
    'classes' => array(),
    'wrappers' => array(
      'thumbnail_image' => 'div',
      'caption' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['commerce_product|sewing_kit|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'commerce_product|sewing_kit|node_full';
  $ds_layout->entity_type = 'commerce_product';
  $ds_layout->bundle = 'sewing_kit';
  $ds_layout->view_mode = 'node_full';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_leading_image',
        1 => 'field_extra_info',
        2 => 'field_weight',
        3 => 'commerce_price',
        4 => 'field_more_images',
      ),
    ),
    'fields' => array(
      'field_leading_image' => 'ds_content',
      'field_extra_info' => 'ds_content',
      'field_weight' => 'ds_content',
      'commerce_price' => 'ds_content',
      'field_more_images' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['commerce_product|sewing_kit|node_full'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'commerce_product|sewing_kit|node_teaser';
  $ds_layout->entity_type = 'commerce_product';
  $ds_layout->bundle = 'sewing_kit';
  $ds_layout->view_mode = 'node_teaser';
  $ds_layout->layout = 'panels-bootstrap_thumbnail';
  $ds_layout->settings = array(
    'regions' => array(
      'thumbnail_image' => array(
        0 => 'field_leading_image',
      ),
      'caption' => array(
        1 => 'title',
        2 => 'field_extra_info',
        3 => 'commerce_price',
      ),
    ),
    'fields' => array(
      'field_leading_image' => 'thumbnail_image',
      'title' => 'caption',
      'field_extra_info' => 'caption',
      'commerce_price' => 'caption',
    ),
    'classes' => array(),
    'wrappers' => array(
      'thumbnail_image' => 'div',
      'caption' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['commerce_product|sewing_kit|node_teaser'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|cloth_display|full';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'cloth_display';
  $ds_layout->view_mode = 'full';
  $ds_layout->layout = 'panels-sutro_double';
  $ds_layout->settings = array(
    'regions' => array(
      'column1' => array(
        0 => 'product:field_leading_image',
      ),
      'column2' => array(
        1 => 'title',
        2 => 'product:field_extra_info',
        3 => 'product:field_dimensions',
        4 => 'product:field_brand',
        5 => 'product:field_cloth_type',
        6 => 'product:field_cloth_style',
        7 => 'product:field_color',
        8 => 'product:commerce_price',
        9 => 'product:field_price_per_meter',
        10 => 'field_products',
      ),
      'footer' => array(
        11 => 'product:field_more_images',
        12 => 'links',
      ),
    ),
    'fields' => array(
      'product:field_leading_image' => 'column1',
      'title' => 'column2',
      'product:field_extra_info' => 'column2',
      'product:field_dimensions' => 'column2',
      'product:field_brand' => 'column2',
      'product:field_cloth_type' => 'column2',
      'product:field_cloth_style' => 'column2',
      'product:field_color' => 'column2',
      'product:commerce_price' => 'column2',
      'product:field_price_per_meter' => 'column2',
      'field_products' => 'column2',
      'product:field_more_images' => 'footer',
      'links' => 'footer',
    ),
    'classes' => array(),
    'wrappers' => array(
      'header' => 'div',
      'column1' => 'div',
      'column2' => 'div',
      'middle' => 'div',
      'secondcolumn1' => 'div',
      'secondcolumn2' => 'div',
      'footer' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|cloth_display|full'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|cloth_display|teaser';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'cloth_display';
  $ds_layout->view_mode = 'teaser';
  $ds_layout->layout = 'panels-bootstrap_thumbnail';
  $ds_layout->settings = array(
    'regions' => array(
      'thumbnail_image' => array(
        0 => 'product:field_leading_image',
      ),
      'caption' => array(
        1 => 'title',
        2 => 'product:field_dimensions',
        3 => 'product:commerce_price',
        4 => 'field_products',
      ),
    ),
    'fields' => array(
      'product:field_leading_image' => 'thumbnail_image',
      'title' => 'caption',
      'product:field_dimensions' => 'caption',
      'product:commerce_price' => 'caption',
      'field_products' => 'caption',
    ),
    'classes' => array(),
    'wrappers' => array(
      'thumbnail_image' => 'div',
      'caption' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|cloth_display|teaser'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|sewing_kit_display|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'sewing_kit_display';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'product:field_extra_info',
        1 => 'product:field_weight',
      ),
      'right' => array(
        2 => 'product:commerce_price',
        3 => 'field_products',
      ),
      'footer' => array(
        4 => 'product:field_more_images',
      ),
    ),
    'fields' => array(
      'product:field_extra_info' => 'left',
      'product:field_weight' => 'left',
      'product:commerce_price' => 'right',
      'field_products' => 'right',
      'product:field_more_images' => 'footer',
    ),
    'classes' => array(),
    'wrappers' => array(
      'header' => 'div',
      'left' => 'div',
      'right' => 'div',
      'footer' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|sewing_kit_display|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|sewing_kit_display|full';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'sewing_kit_display';
  $ds_layout->view_mode = 'full';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'product:field_leading_image',
      ),
      'right' => array(
        1 => 'title',
        2 => 'product:field_extra_info',
        3 => 'product:commerce_price',
        4 => 'field_products',
      ),
      'footer' => array(
        5 => 'product:field_more_images',
        6 => 'links',
      ),
    ),
    'fields' => array(
      'product:field_leading_image' => 'left',
      'title' => 'right',
      'product:field_extra_info' => 'right',
      'product:commerce_price' => 'right',
      'field_products' => 'right',
      'product:field_more_images' => 'footer',
      'links' => 'footer',
    ),
    'classes' => array(),
    'wrappers' => array(
      'header' => 'div',
      'left' => 'div',
      'right' => 'div',
      'footer' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|sewing_kit_display|full'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|sewing_kit_display|teaser';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'sewing_kit_display';
  $ds_layout->view_mode = 'teaser';
  $ds_layout->layout = 'panels-bootstrap_thumbnail';
  $ds_layout->settings = array(
    'regions' => array(
      'thumbnail_image' => array(
        0 => 'product:field_leading_image',
      ),
      'caption' => array(
        1 => 'title',
        2 => 'product:commerce_price',
        3 => 'field_products',
      ),
    ),
    'fields' => array(
      'product:field_leading_image' => 'thumbnail_image',
      'title' => 'caption',
      'product:commerce_price' => 'caption',
      'field_products' => 'caption',
    ),
    'classes' => array(),
    'wrappers' => array(
      'thumbnail_image' => 'div',
      'caption' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|sewing_kit_display|teaser'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|voucher_display|teaser';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'voucher_display';
  $ds_layout->view_mode = 'teaser';
  $ds_layout->layout = 'panels-bootstrap_thumbnail';
  $ds_layout->settings = array(
    'regions' => array(
      'thumbnail_image' => array(
        0 => 'product:field_leading_image',
      ),
      'caption' => array(
        1 => 'title',
        2 => 'body',
        3 => 'field_products',
      ),
    ),
    'fields' => array(
      'product:field_leading_image' => 'thumbnail_image',
      'title' => 'caption',
      'body' => 'caption',
      'field_products' => 'caption',
    ),
    'classes' => array(),
    'wrappers' => array(
      'thumbnail_image' => 'div',
      'caption' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|voucher_display|teaser'] = $ds_layout;

  return $export;
}

/**
 * Implements hook_ds_view_modes_info().
 */
function creating_webshop_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'teaser';
  $ds_view_mode->label = 'Teaser';
  $ds_view_mode->entities = array(
    'commerce_line_item' => 'commerce_line_item',
    'commerce_product' => 'commerce_product',
  );
  $export['teaser'] = $ds_view_mode;

  return $export;
}
