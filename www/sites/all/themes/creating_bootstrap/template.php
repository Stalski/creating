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
  $data = menu_tree_all_data('main-menu');
  $tree = menu_tree_output($data);
  $tree['#theme_wrappers'] = array('menu_tree__primary');
  $variables['primary_nav'] = drupal_render($tree);

}

/**
 * Implements hook_process_page().
 *
 * @see page.tpl.php
 */
function creating_bootstrap_process_page(&$variables) {
  // classes array adjustments.
}
