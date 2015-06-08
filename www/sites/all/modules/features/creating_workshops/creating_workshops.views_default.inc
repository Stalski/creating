<?php
/**
 * @file
 * creating_workshops.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function creating_workshops_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'workshops';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Workshops';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Workshop gallery';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'meer';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Toepassen';
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Opnieuw instellen';
  $handler->display->display_options['exposed_form']['options']['exposed_sorts_label'] = 'Sorteren op';
  $handler->display->display_options['exposed_form']['options']['sort_asc_label'] = 'Oplopend';
  $handler->display->display_options['exposed_form']['options']['sort_desc_label'] = 'Aflopend';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* Veld: Inhoud: Kalender */
  $handler->display->display_options['fields']['field_calendar']['id'] = 'field_calendar';
  $handler->display->display_options['fields']['field_calendar']['table'] = 'field_data_field_calendar';
  $handler->display->display_options['fields']['field_calendar']['field'] = 'field_calendar';
  $handler->display->display_options['fields']['field_calendar']['label'] = '';
  $handler->display->display_options['fields']['field_calendar']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_calendar']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_calendar']['delta_offset'] = '0';
  /* Veld: Inhoud: Titel */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Sorteercriterium: Inhoud: Datum van inzending */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextueel filter: Inhoud: Kalender - startdatum (field_calendar) */
  $handler->display->display_options['arguments']['field_calendar_value']['id'] = 'field_calendar_value';
  $handler->display->display_options['arguments']['field_calendar_value']['table'] = 'field_data_field_calendar';
  $handler->display->display_options['arguments']['field_calendar_value']['field'] = 'field_calendar_value';
  $handler->display->display_options['arguments']['field_calendar_value']['exception']['title'] = 'Alle';
  $handler->display->display_options['arguments']['field_calendar_value']['default_argument_type'] = 'date';
  $handler->display->display_options['arguments']['field_calendar_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_calendar_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_calendar_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_calendar_value']['add_delta'] = 'yes';
  /* Filtercriterium: Inhoud: Gepubliceerd */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filtercriterium: Inhoud: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'workshop' => 'workshop',
  );

  /* Display: All workshops (sort postdate) */
  $handler = $view->new_display('block', 'All workshops (sort postdate)', 'block');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'All workshops sorted by postdate';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Veld: Inhoud: Kalender */
  $handler->display->display_options['fields']['field_calendar']['id'] = 'field_calendar';
  $handler->display->display_options['fields']['field_calendar']['table'] = 'field_data_field_calendar';
  $handler->display->display_options['fields']['field_calendar']['field'] = 'field_calendar';
  $handler->display->display_options['fields']['field_calendar']['label'] = '';
  $handler->display->display_options['fields']['field_calendar']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_calendar']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_calendar']['delta_offset'] = '0';
  /* Veld: Inhoud: Titel */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sorteercriterium: Inhoud: Kalender - startdatum (field_calendar) */
  $handler->display->display_options['sorts']['field_calendar_value']['id'] = 'field_calendar_value';
  $handler->display->display_options['sorts']['field_calendar_value']['table'] = 'field_data_field_calendar';
  $handler->display->display_options['sorts']['field_calendar_value']['field'] = 'field_calendar_value';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextueel filter: Datum: Datum (node) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'node';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['exception']['title'] = 'Alle';
  $handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
  $handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_calendar.field_calendar_value' => 'field_data_field_calendar.field_calendar_value',
  );
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filtercriterium: Inhoud: Gepubliceerd */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filtercriterium: Inhoud: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'workshop' => 'workshop',
  );
  /* Filtercriterium: Inhoud: Kalender - startdatum (field_calendar) */
  $handler->display->display_options['filters']['field_calendar_value']['id'] = 'field_calendar_value';
  $handler->display->display_options['filters']['field_calendar_value']['table'] = 'field_data_field_calendar';
  $handler->display->display_options['filters']['field_calendar_value']['field'] = 'field_calendar_value';
  $handler->display->display_options['filters']['field_calendar_value']['operator'] = '>=';
  $handler->display->display_options['filters']['field_calendar_value']['form_type'] = 'date_text';
  $handler->display->display_options['filters']['field_calendar_value']['default_date'] = 'now';
  $handler->display->display_options['block_description'] = 'All workshops';

  /* Display: Upcoming workshops */
  $handler = $view->new_display('block', 'Upcoming workshops', 'block_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Upcoming workshops';
  $handler->display->display_options['defaults']['use_more'] = FALSE;
  $handler->display->display_options['use_more'] = TRUE;
  $handler->display->display_options['defaults']['use_more_always'] = FALSE;
  $handler->display->display_options['defaults']['use_more_always'] = FALSE;
  $handler->display->display_options['use_more_always'] = TRUE;
  $handler->display->display_options['defaults']['use_more_text'] = FALSE;
  $handler->display->display_options['use_more_text'] = 'Alle workshops';
  $handler->display->display_options['defaults']['link_display'] = FALSE;
  $handler->display->display_options['link_display'] = 'custom_url';
  $handler->display->display_options['link_url'] = 'kalender';
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_calendar_1',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Kop: Algemeen: Tekstveld */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['label'] = 'Workshop types';
  $handler->display->display_options['header']['area']['content'] = '<a href="/enige-ervaring">Enige ervaring</a> | <a href="Beginners">Beginners</a> | <a href="/workshop-jongeren">Jongeren</a>';
  $handler->display->display_options['header']['area']['format'] = 'panopoly_wysiwyg_text';
  $handler->display->display_options['defaults']['footer'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Veld: Inhoud: Kalender */
  $handler->display->display_options['fields']['field_calendar_1']['id'] = 'field_calendar_1';
  $handler->display->display_options['fields']['field_calendar_1']['table'] = 'field_data_field_calendar';
  $handler->display->display_options['fields']['field_calendar_1']['field'] = 'field_calendar';
  $handler->display->display_options['fields']['field_calendar_1']['label'] = '';
  $handler->display->display_options['fields']['field_calendar_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_calendar_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_calendar_1']['settings'] = array(
    'format_type' => 'panopoly_day',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_calendar_1']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_calendar_1']['delta_offset'] = '0';
  /* Veld: Inhoud: Kalender */
  $handler->display->display_options['fields']['field_calendar']['id'] = 'field_calendar';
  $handler->display->display_options['fields']['field_calendar']['table'] = 'field_data_field_calendar';
  $handler->display->display_options['fields']['field_calendar']['field'] = 'field_calendar';
  $handler->display->display_options['fields']['field_calendar']['label'] = '';
  $handler->display->display_options['fields']['field_calendar']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_calendar']['settings'] = array(
    'format_type' => 'panopoly_time',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_calendar']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_calendar']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_calendar']['multi_type'] = 'ol';
  /* Veld: Inhoud: Titel */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sorteercriterium: Inhoud: Kalender - startdatum (field_calendar) */
  $handler->display->display_options['sorts']['field_calendar_value']['id'] = 'field_calendar_value';
  $handler->display->display_options['sorts']['field_calendar_value']['table'] = 'field_data_field_calendar';
  $handler->display->display_options['sorts']['field_calendar_value']['field'] = 'field_calendar_value';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextueel filter: Datum: Datum (node) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'node';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['exception']['title'] = 'Alle';
  $handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
  $handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_calendar.field_calendar_value' => 'field_data_field_calendar.field_calendar_value',
  );
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filtercriterium: Inhoud: Gepubliceerd */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filtercriterium: Inhoud: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'workshop' => 'workshop',
  );
  /* Filtercriterium: Inhoud: Kalender - startdatum (field_calendar) */
  $handler->display->display_options['filters']['field_calendar_value']['id'] = 'field_calendar_value';
  $handler->display->display_options['filters']['field_calendar_value']['table'] = 'field_data_field_calendar';
  $handler->display->display_options['filters']['field_calendar_value']['field'] = 'field_calendar_value';
  $handler->display->display_options['filters']['field_calendar_value']['operator'] = '>=';
  $handler->display->display_options['filters']['field_calendar_value']['form_type'] = 'date_text';
  $handler->display->display_options['filters']['field_calendar_value']['default_date'] = 'now';
  /* Filtercriterium: Inhoud: Kalender - startdatum (field_calendar) */
  $handler->display->display_options['filters']['field_calendar_value_1']['id'] = 'field_calendar_value_1';
  $handler->display->display_options['filters']['field_calendar_value_1']['table'] = 'field_data_field_calendar';
  $handler->display->display_options['filters']['field_calendar_value_1']['field'] = 'field_calendar_value';
  $handler->display->display_options['filters']['field_calendar_value_1']['operator'] = '<';
  $handler->display->display_options['filters']['field_calendar_value_1']['form_type'] = 'date_text';
  $handler->display->display_options['filters']['field_calendar_value_1']['default_date'] = 'now + 30 days';
  $handler->display->display_options['block_description'] = 'Upcoming workshops';

  /* Display: Upcoming workshops page */
  $handler = $view->new_display('block', 'Upcoming workshops page', 'block_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Upcoming workshops page';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['row_class'] = 'list-group-item';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['style_options']['class'] = 'list-group';
  $handler->display->display_options['style_options']['wrapper_class'] = '';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Veld: Inhoud: Titel */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Veld: Inhoud: Kalender */
  $handler->display->display_options['fields']['field_calendar']['id'] = 'field_calendar';
  $handler->display->display_options['fields']['field_calendar']['table'] = 'field_data_field_calendar';
  $handler->display->display_options['fields']['field_calendar']['field'] = 'field_calendar';
  $handler->display->display_options['fields']['field_calendar']['label'] = '';
  $handler->display->display_options['fields']['field_calendar']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_calendar']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_calendar']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_calendar']['delta_offset'] = '0';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sorteercriterium: Inhoud: Kalender - startdatum (field_calendar) */
  $handler->display->display_options['sorts']['field_calendar_value']['id'] = 'field_calendar_value';
  $handler->display->display_options['sorts']['field_calendar_value']['table'] = 'field_data_field_calendar';
  $handler->display->display_options['sorts']['field_calendar_value']['field'] = 'field_calendar_value';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextueel filter: Datum: Datum (node) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'node';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['exception']['title'] = 'Alle';
  $handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
  $handler->display->display_options['arguments']['date_argument']['add_delta'] = 'yes';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_calendar.field_calendar_value' => 'field_data_field_calendar.field_calendar_value',
  );
  $handler->display->display_options['block_description'] = 'Upcoming workshops page';

  /* Display: Images from previous workshops */
  $handler = $view->new_display('block', 'Images from previous workshops', 'block_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Workshop gallery';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entity';
  $handler->display->display_options['row_options']['view_mode'] = 'slideshow';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filtercriterium: Inhoud: Gepubliceerd */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filtercriterium: Inhoud: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'workshop' => 'workshop',
  );

  /* Display: Calendar  workshops */
  $handler = $view->new_display('block', 'Calendar  workshops', 'workshop_calendar');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Kalender';
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'date_views_pager';
  $handler->display->display_options['pager']['options']['pager_position'] = 'bottom';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'calendar_style';
  $handler->display->display_options['style_options']['name_size'] = '3';
  $handler->display->display_options['style_options']['mini'] = '0';
  $handler->display->display_options['style_options']['with_weekno'] = '0';
  $handler->display->display_options['style_options']['multiday_theme'] = '1';
  $handler->display->display_options['style_options']['theme_style'] = '1';
  $handler->display->display_options['style_options']['max_items'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'calendar_entity';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  $handler->display->display_options['row_options']['colors']['legend'] = 'type';
  $handler->display->display_options['row_options']['colors']['calendar_colors_type'] = array(
    'cloth_display' => '#89a53e',
    'contactform' => '#CCCCCC',
    'featured_page' => '#e45f5f',
    'panopoly_page' => '#63ff77',
    'sewing_kit_display' => '#c71212',
    'album' => '#eee841',
    'voucher_display' => '#512c2c',
    'workshop' => '#2a2b8b',
  );
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Veld: Inhoud: Kalender */
  $handler->display->display_options['fields']['field_calendar']['id'] = 'field_calendar';
  $handler->display->display_options['fields']['field_calendar']['table'] = 'field_data_field_calendar';
  $handler->display->display_options['fields']['field_calendar']['field'] = 'field_calendar';
  $handler->display->display_options['fields']['field_calendar']['label'] = '';
  $handler->display->display_options['fields']['field_calendar']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_calendar']['settings'] = array(
    'format_type' => 'panopoly_time',
    'fromto' => 'value',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_calendar']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_calendar']['delta_offset'] = '0';
  /* Veld: Inhoud: Titel */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sorteercriterium: Inhoud: Kalender - startdatum (field_calendar) */
  $handler->display->display_options['sorts']['field_calendar_value']['id'] = 'field_calendar_value';
  $handler->display->display_options['sorts']['field_calendar_value']['table'] = 'field_data_field_calendar';
  $handler->display->display_options['sorts']['field_calendar_value']['field'] = 'field_calendar_value';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextueel filter: Datum: Datum (node) */
  $handler->display->display_options['arguments']['date_argument']['id'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['table'] = 'node';
  $handler->display->display_options['arguments']['date_argument']['field'] = 'date_argument';
  $handler->display->display_options['arguments']['date_argument']['default_action'] = 'default';
  $handler->display->display_options['arguments']['date_argument']['exception']['title'] = 'Alle';
  $handler->display->display_options['arguments']['date_argument']['default_argument_type'] = 'date';
  $handler->display->display_options['arguments']['date_argument']['date_fields'] = array(
    'field_data_field_calendar.field_calendar_value' => 'field_data_field_calendar.field_calendar_value',
  );
  $handler->display->display_options['arguments']['date_argument']['date_method'] = 'AND';
  $handler->display->display_options['block_description'] = 'Calendar workshops';
  $translatables['workshops'] = array(
    t('Master'),
    t('Workshop gallery'),
    t('meer'),
    t('Toepassen'),
    t('Opnieuw instellen'),
    t('Sorteren op'),
    t('Oplopend'),
    t('Aflopend'),
    t('Alle'),
    t('All workshops (sort postdate)'),
    t('All workshops sorted by postdate'),
    t('All workshops'),
    t('Upcoming workshops'),
    t('Alle workshops'),
    t('Workshop types'),
    t('<a href="/enige-ervaring">Enige ervaring</a> | <a href="Beginners">Beginners</a> | <a href="/workshop-jongeren">Jongeren</a>'),
    t('Upcoming workshops page'),
    t('Images from previous workshops'),
    t('Calendar  workshops'),
    t('Kalender'),
    t('Calendar workshops'),
  );
  $export['workshops'] = $view;

  return $export;
}
