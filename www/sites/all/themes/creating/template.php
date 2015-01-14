<?php
/**
 * @file
 * Provides overrides and additions to aid the theme.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Adds a placeholder to the search block.
 */
function creating_form_search_block_form_alter(&$form, &$form_state, $form_id) {
  $form['search_block_form']['#attributes']['placeholder'] = t('Search…');
}

/**
 * Implements hook_css_alter().
 */
function creating_css_alter(&$css) {

  /* Remove some default Drupal css */
  $exclude = array(
    'modules/aggregator/aggregator.css' => FALSE,
    'modules/block/block.css' => FALSE,
    'modules/book/book.css' => FALSE,
    'modules/comment/comment.css' => FALSE,
    'modules/dblog/dblog.css' => FALSE,
    'modules/field/theme/field.css' => FALSE,
    'modules/file/file.css' => FALSE,
    'modules/filter/filter.css' => FALSE,
    'modules/forum/forum.css' => FALSE,
    'modules/help/help.css' => FALSE,
    // 'modules/menu/menu.css' => FALSE,
    'modules/node/node.css' => FALSE,
    'modules/openid/openid.css' => FALSE,
    'modules/poll/poll.css' => FALSE,
    'modules/profile/profile.css' => FALSE,
    'modules/search/search.css' => FALSE,
    'modules/statistics/statistics.css' => FALSE,
    'modules/syslog/syslog.css' => FALSE,
    'modules/system/admin.css' => FALSE,
    'modules/system/maintenance.css' => FALSE,
    // 'modules/system/system.css' => FALSE,
    // 'modules/system/system.admin.css' => FALSE,
    'modules/system/system.maintenance.css' => FALSE,
    'modules/system/system.messages.css' => FALSE,
    // 'modules/system/system.theme.css' => FALSE,
    // 'modules/system/system.menus.css' => FALSE,
    'modules/taxonomy/taxonomy.css' => FALSE,
    'modules/tracker/tracker.css' => FALSE,
    'modules/update/update.css' => FALSE,
    'modules/user/user.css' => FALSE,
    'sites/all/modules/contrib/panels/css/panels.css' => FALSE,
  );

  $css = array_diff_key($css, $exclude);

  /* Get rid of some default panel css */
  foreach ($css as $path => $meta) {
    if (strpos($path, 'threecol_33_34_33_stacked') !== FALSE || strpos($path, 'threecol_25_50_25_stacked') !== FALSE) {
      unset($css[$path]);
    }
  }
}

/**
 * Override or insert variables into the html template.
 *
 * @param $variables
 *   An array of variables to pass to the theme template.
 * @param $hook
 *   The name of the template being rendered. This is usually "html", but can
 *   also be "maintenance_page" since zen_preprocess_maintenance_page() calls
 *   this function to have consistent variables.
 */
function creating_preprocess_html(&$variables, $hook) {

}

/**
 * Implements theme_breadcrumb()
 *
 * Return a themed breadcrumb trail.
 *
 * @param $breadcrumb
 *   An array containing the breadcrumb links.
 * @return a string containing the breadcrumb output.
 */
function creating_breadcrumb($variables) {
  $item = menu_get_item();
  $variables['breadcrumb'][] = drupal_get_title();
  $breadcrumb = $variables['breadcrumb'];

  if (!empty($breadcrumb)) {
    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .element-invisible.
    $output = '<h2 class="element-invisible">' . t('You are here') . '</h2>';
    $output .= '<div class="breadcrumb">' . implode(' > ', $breadcrumb) . '</div>';

    return $output;
  }
}

function creating_preprocess_page(&$variables){

  // Check if we are using panels for this page
  /*$variables['page']['use_panels'] = FALSE;
  if (panels_get_current_page_display()) {
     $variables['page']['use_panels'] = TRUE;
  }*/
}

/*
 * Add some custom block classes.
 */
function creating_preprocess_block(&$variables){

  // Remove unused default classes
  $original_classes = $variables['classes_array'];

  $to_remove = array();
  $to_remove[] = 'block';
  $to_remove[] = 'block-block';
  $to_remove[] = 'block-system';
  $to_remove[] = 'block-menu-block';

  // No contextual links in the navigation reason, for css positioning reasons.
  //dsm($variables);
  $variables['classes_array'] = array_diff($original_classes, $to_remove);

}

/**
 * Render callback.
 *
 * @ingroup themeable
 */
function creating_panels_default_style_render_region($variables) {
  $output = '';
//  $output .= '<div class="region region-' . $vars['region_id'] . '">';
  $output .= implode('', $variables['panes']);
//  $output .= '</div>';
  return $output;
}

/**
 * Clean up the panel pane variables for the template.
 */
function creating_preprocess_panels_pane(&$variables) {
  if (isset($variables['content']['#entity_type']) && $variables['content']['#entity_type'] == 'fieldable_panels_pane') {
    $variables['classes_array'] = array('contextual-links-region', 'cta', str_replace('_', '-', $variables['content']['#bundle']));
  }
}




