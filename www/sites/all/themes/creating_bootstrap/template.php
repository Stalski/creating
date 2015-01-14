<?php
/**
 * @file
 * page.vars.php
 */

/**
 * Implements hook_preprocess_page().
 *
 * @see page.tpl.php
 */
function creating_bootstrap_preprocess_page(&$variables) {

  // Primary nav.
  $config = menu_block_get_config('1');
  $data = menu_tree_build($config);
  $variables['primary_nav'] = $data['content'];
  $variables['primary_nav']['#theme_wrappers'] = array('menu_tree__primary');


}

/**
 * Implements hook_process_page().
 *
 * @see page.tpl.php
 */
function creating_bootstrap_process_page(&$variables) {
  // classes array adjustments.
}
