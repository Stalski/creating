<?php
/**
 * @file
 * creating_webshop.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function creating_webshop_taxonomy_default_vocabularies() {
  return array(
    'brand' => array(
      'name' => 'Designer',
      'machine_name' => 'brand',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'cloth_theme' => array(
      'name' => 'Thema',
      'machine_name' => 'cloth_theme',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'cloth_type' => array(
      'name' => 'Soort stof',
      'machine_name' => 'cloth_type',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
    'color' => array(
      'name' => 'Kleur',
      'machine_name' => 'color',
      'description' => '',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
