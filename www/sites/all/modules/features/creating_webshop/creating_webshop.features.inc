<?php
/**
 * @file
 * creating_webshop.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function creating_webshop_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function creating_webshop_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function creating_webshop_image_default_styles() {
  $styles = array();

  // Exported image style: cart_product_thumb.
  $styles['cart_product_thumb'] = array(
    'name' => 'cart_product_thumb',
    'label' => 'cart_product_thumb',
    'effects' => array(
      9 => array(
        'label' => 'Schalen',
        'help' => 'Door te schalen worden de originele verhoudingen behouden. Als één van de dimensies wordt ingevuld zal de andere worden berekend.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 60,
          'height' => 60,
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: featured_full_width.
  $styles['featured_full_width'] = array(
    'name' => 'featured_full_width',
    'label' => 'featured_full_width (750x250)',
    'effects' => array(
      14 => array(
        'label' => 'Schalen en bijsnijden',
        'help' => 'Bij het schalen blijft de breedte-hoogte verhouding van de oorspronkelijke afbeelding behouden. Bij het bijsnijden wordt de langste zijde ingekort. Hiermee kunt u bijvoorbeeld vierkante miniaturen maken.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 750,
          'height' => 250,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: full_width.
  $styles['full_width'] = array(
    'name' => 'full_width',
    'label' => 'full_width',
    'effects' => array(
      13 => array(
        'label' => 'Schalen en bijsnijden',
        'help' => 'Bij het schalen blijft de breedte-hoogte verhouding van de oorspronkelijke afbeelding behouden. Bij het bijsnijden wordt de langste zijde ingekort. Hiermee kunt u bijvoorbeeld vierkante miniaturen maken.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 1024,
          'height' => 320,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: naaipakket_big.
  $styles['naaipakket_big'] = array(
    'name' => 'naaipakket_big',
    'label' => 'naaipakket_big',
    'effects' => array(
      5 => array(
        'label' => 'Schalen',
        'help' => 'Door te schalen worden de originele verhoudingen behouden. Als één van de dimensies wordt ingevuld zal de andere worden berekend.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 470,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: naaipakket_featured.
  $styles['naaipakket_featured'] = array(
    'name' => 'naaipakket_featured',
    'label' => 'naaipakket_featured',
    'effects' => array(
      6 => array(
        'label' => 'Schalen en bijsnijden',
        'help' => 'Bij het schalen blijft de breedte-hoogte verhouding van de oorspronkelijke afbeelding behouden. Bij het bijsnijden wordt de langste zijde ingekort. Hiermee kunt u bijvoorbeeld vierkante miniaturen maken.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 276,
          'height' => 208,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: product_teaser.
  $styles['product_teaser'] = array(
    'name' => 'product_teaser',
    'label' => 'product_teaser',
    'effects' => array(
      12 => array(
        'label' => 'Schalen en bijsnijden',
        'help' => 'Bij het schalen blijft de breedte-hoogte verhouding van de oorspronkelijke afbeelding behouden. Bij het bijsnijden wordt de langste zijde ingekort. Hiermee kunt u bijvoorbeeld vierkante miniaturen maken.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 250,
          'height' => 250,
        ),
        'weight' => -10,
      ),
    ),
  );

  // Exported image style: sidebar_pictures_slideshow.
  $styles['sidebar_pictures_slideshow'] = array(
    'name' => 'sidebar_pictures_slideshow',
    'label' => 'sidebar_pictures_slideshow',
    'effects' => array(
      7 => array(
        'label' => 'Schalen',
        'help' => 'Door te schalen worden de originele verhoudingen behouden. Als één van de dimensies wordt ingevuld zal de andere worden berekend.',
        'effect callback' => 'image_scale_effect',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 540,
          'height' => '',
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
      10 => array(
        'label' => 'Bijsnijden',
        'help' => 'Door bij te snijden worden delen van een afbeelding verwijderd zodat deze binnen de opgegeven maten past.',
        'effect callback' => 'image_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_crop_form',
        'summary theme' => 'image_crop_summary',
        'module' => 'image',
        'name' => 'image_crop',
        'data' => array(
          'width' => 540,
          'height' => 405,
          'anchor' => 'center-center',
        ),
        'weight' => 2,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function creating_webshop_node_info() {
  $items = array(
    'cloth_display' => array(
      'name' => t('Cloth display'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'sewing_kit_display' => array(
      'name' => t('Sewing kit display'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'voucher_display' => array(
      'name' => t('Voucher Display'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
