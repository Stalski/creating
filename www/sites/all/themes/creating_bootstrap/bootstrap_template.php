<?php
/**
 * @file
 * Preprocess extra drupal or contribs elements so they are converted into
 * bootstrap html / css.
 */

/**
 * Implements hook_preprocess_views_view_grid().
 */
function creating_bootstrap_preprocess_views_view_grid(&$vars) {

  if (!empty($vars['view']->style_options)) {
    $number_of_columns = $vars['view']->style_options['columns'];
    if ($number_of_columns == 4) {
      $column_class = "col-xs-6 col-md-3";
    }
    elseif ($number_of_columns == 3) {
      $column_class = "col-md-4";
    }
    elseif ($number_of_columns == 6) {
      $column_class = "col-md-2";
    }
  }
  else {
    $column_class = "col-md-12";
  }

  if (isset($column_class)) {
    foreach ($vars['column_classes'] as $delta => $rows) {

      // Change the column classes to bootstraps grid columns.
      foreach ($rows as $column_delta => $columns) {
        $vars['column_classes'][$delta][$column_delta] = $column_class;
      }
      // Change the row classes to bootstrap grid rows.
      $vars['row_classes'][$delta] = "row";

    }
  }

  // Bootstrap does not need a wrapper for the rows.
  $vars['classes_array'] = array();
  $vars['class'] = "";

}

/**
 * Overrides theme_status_messages().
 */
function creating_bootstrap_status_messages($variables) {
  $display = $variables['display'];
  $output = '';

  $status_heading = array(
    'status' => t('Status message'),
    'error' => t('Error message'),
    'warning' => t('Warning message'),
    'info' => t('Informative message'),
    'commerce-add-to-cart-confirmation' => t('Confirmation messages'),
  );

  // Map Drupal message types to their corresponding Bootstrap classes.
  // @see http://twitter.github.com/bootstrap/components.html#alerts
  $status_class = array(
    'status' => 'success',
    'error' => 'danger',
    'warning' => 'warning',
    // Not supported, but in theory a module could send any type of message.
    // @see drupal_set_message()
    // @see theme_status_messages()
    'info' => 'info',

    // Custom messages.
    'commerce-add-to-cart-confirmation' => 'commerce-add-to-cart-confirmation',
  );

  foreach (drupal_get_messages($display) as $type => $messages) {

    if ($type == 'commerce-add-to-cart-confirmation') {
      $class = "alert messages commerce-add-to-cart-confirmation";
    }
    else {
      $class = (isset($status_class[$type])) ? ' alert-' . $status_class[$type] : '';
    }
    $output .= "<div class=\"alert alert-block$class\">\n";
    $output .= "  <a class=\"close\" data-dismiss=\"alert\" href=\"#\">&times;</a>\n";

    if (!empty($status_heading[$type])) {
      $output .= '<h4 class="element-invisible">' . $status_heading[$type] . "</h4>\n";
    }

    if (count($messages) > 1) {
      $output .= " <ul>\n";
      foreach ($messages as $message) {
        $output .= '  <li>' . $message . "</li>\n";
      }
      $output .= " </ul>\n";
    }
    else {
      $output .= $messages[0];
    }

    $output .= "</div>\n";
  }
  return $output;
}
