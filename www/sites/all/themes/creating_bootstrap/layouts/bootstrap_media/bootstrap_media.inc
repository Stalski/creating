<?php

/**
 * implementation of hook_panels_layouts()
 */
// Plugin definition
$plugin = array(
  'title' => t('Bootstrap media'),
  'category' => t('Columns: 2'),
  'icon' => 'bootstrap_media.png',
  'theme' => 'bootstrap-media',
  /*'css' => 'bootstrap_media.css',*/
  'regions' => array(
    'media_left' => t('Media Left'),
    'media_body' => t('Media Body')
  ),
);
