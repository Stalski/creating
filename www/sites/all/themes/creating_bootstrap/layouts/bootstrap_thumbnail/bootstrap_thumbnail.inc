<?php

/**
 * implementation of hook_panels_layouts()
 */
// Plugin definition
$plugin = array(
  'title' => t('Bootstrap thumbnail'),
  'category' => t('Columns: 1'),
  'icon' => 'bootstrap_thumbnail.png',
  'theme' => 'bootstrap-thumbnail',
  'css' => 'bootstrap_thumbnail.css',
  'regions' => array(
    'thumbnail_image' => t('Thumbnail image'),
    'caption' => t('Caption')
  ),
);
