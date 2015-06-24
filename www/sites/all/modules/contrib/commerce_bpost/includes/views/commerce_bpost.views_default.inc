<?php

/**
 * @file
 * Views listing bpost orders
 */

/**
 * Implements hook_views_default_views_alter().
 *
 * Alter commerce_order default views to add the "bpost orders" display.
 */
function commerce_bpost_views_default_views_alter(&$views) {
  if (isset($views['commerce_backoffice_orders'])) {
    $commerce_bpost_settings = variable_get('commerce_bpost_settings', array());

    /* Display: bpost open orders */
    $handler = $views['commerce_backoffice_orders']->new_display('page', 'bpost open orders', 'bpost_open_orders');
    $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
    $handler->display->display_options['defaults']['access'] = FALSE;
    $handler->display->display_options['access']['type'] = 'commerce_bpost';
    $handler->display->display_options['defaults']['relationships'] = FALSE;
    $handler->display->display_options['path'] = 'admin/commerce/orders/bpost-orders/open';
    $handler->display->display_options['menu']['type'] = 'default tab';
    $handler->display->display_options['menu']['title'] = 'Open';
    $handler->display->display_options['menu']['weight'] = '-8';
    $handler->display->display_options['menu']['context'] = 0;
    $handler->display->display_options['menu']['context_only_inline'] = 0;
    $handler->display->display_options['tab_options']['type'] = 'tab';
    $handler->display->display_options['tab_options']['title'] = 'bpost orders';
    $handler->display->display_options['tab_options']['description'] = 'Manage orders in the store.';
    $handler->display->display_options['tab_options']['weight'] = '';
    $handler->display->display_options['tab_options']['name'] = 'management';
    /* Relationship: Commerce Order: Referenced customer profile */
    $handler->display->display_options['relationships']['commerce_customer_shipping_profile_id']['id'] = 'commerce_customer_shipping_profile_id';
    $handler->display->display_options['relationships']['commerce_customer_shipping_profile_id']['table'] = 'field_data_commerce_customer_shipping';
    $handler->display->display_options['relationships']['commerce_customer_shipping_profile_id']['field'] = 'commerce_customer_shipping_profile_id';
    $handler->display->display_options['relationships']['commerce_customer_shipping_profile_id']['label'] = 'Shipping information';
    /* Relationship: Commerce Order: Owner */
    $handler->display->display_options['relationships']['uid']['id'] = 'uid';
    $handler->display->display_options['relationships']['uid']['table'] = 'commerce_order';
    $handler->display->display_options['relationships']['uid']['field'] = 'uid';
    /* Relationship: Commerce Order: Referenced line items */
    $handler->display->display_options['relationships']['commerce_line_items_line_item_id']['id'] = 'commerce_line_items_line_item_id';
    $handler->display->display_options['relationships']['commerce_line_items_line_item_id']['table'] = 'field_data_commerce_line_items';
    $handler->display->display_options['relationships']['commerce_line_items_line_item_id']['field'] = 'commerce_line_items_line_item_id';
    $handler->display->display_options['relationships']['commerce_line_items_line_item_id']['required'] = TRUE;
    $handler->display->display_options['defaults']['fields'] = FALSE;
    /* Field: Bulk operations: Commerce Order */
    $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
    $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'commerce_order';
    $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
    $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
    $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
    $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
    $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
    $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '50';
    $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
      'action::commerce_bpost_print_label' => array(
        'selected' => 1,
        'postpone_processing' => 0,
        'skip_confirmation' => 1,
        'override_label' => 0,
        'label' => '',
      ),
      'action::commerce_bpost_tracking_mail' => array(
        'selected' => 1,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'action::commerce_bpost_create_retour' => array(
        'selected' => 1,
        'postpone_processing' => 0,
        'skip_confirmation' => 1,
        'override_label' => 0,
        'label' => '',
      ),
      'action::commerce_bpost_mark_as_treated' => array(
        'selected' => 1,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'action::commerce_bpost_unlist_order' => array(
        'selected' => 1,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'action::commerce_bpost_cancel_order' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'action::views_bulk_operations_delete_item' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 1,
        'label' => 'Delete order',
      ),
      'action::views_bulk_operations_delete_revision' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'action::views_bulk_operations_script_action' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'action::views_bulk_operations_modify_action' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
        'settings' => array(
          'show_all_tokens' => 1,
          'display_values' => array(
            '_all_' => '_all_',
          ),
        ),
      ),
      'action::views_bulk_operations_argument_selector_action' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
        'settings' => array(
          'url' => '',
        ),
      ),
      'rules_component::commerce_shipping_service_bpost_bpack' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'rules_component::commerce_shipping_service_bpost_home' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'rules_component::commerce_shipping_service_bpost_postoffice_postpoint' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'rules_component::commerce_shipping_service_bpost_world' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'action::system_send_email_action' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'rules_component::rules_commerce_order_status_canceled' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'rules_component::rules_commerce_order_status_cart' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'rules_component::rules_order_status_checkout_checkout' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'rules_component::rules_order_status_checkout_complete' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'rules_component::rules_order_status_checkout_payment' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'rules_component::rules_order_status_checkout_review' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'rules_component::rules_order_status_checkout_shipping' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'rules_component::rules_commerce_order_status_completed' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'rules_component::rules_commerce_order_status_pending' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'rules_component::rules_commerce_order_status_processing' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
    );
    /* Field: Commerce Order: Display a pdf icon if label available */
    $handler->display->display_options['fields']['bpost_pdf_icon']['id'] = 'bpost_pdf_icon';
    $handler->display->display_options['fields']['bpost_pdf_icon']['table'] = 'commerce_order';
    $handler->display->display_options['fields']['bpost_pdf_icon']['field'] = 'bpost_pdf_icon';
    $handler->display->display_options['fields']['bpost_pdf_icon']['label'] = 'Label';
    $handler->display->display_options['fields']['bpost_pdf_icon']['element_label_colon'] = FALSE;
    /* Field: Commerce Order: Order number */
    $handler->display->display_options['fields']['order_number']['id'] = 'order_number';
    $handler->display->display_options['fields']['order_number']['table'] = 'commerce_order';
    $handler->display->display_options['fields']['order_number']['field'] = 'order_number';
    $handler->display->display_options['fields']['order_number']['label'] = 'Order n°';
    /* Field: Commerce Line item: Shipping service */
    $handler->display->display_options['fields']['commerce_shipping_service']['id'] = 'commerce_shipping_service';
    $handler->display->display_options['fields']['commerce_shipping_service']['table'] = 'field_data_commerce_shipping_service';
    $handler->display->display_options['fields']['commerce_shipping_service']['field'] = 'commerce_shipping_service';
    $handler->display->display_options['fields']['commerce_shipping_service']['relationship'] = 'commerce_line_items_line_item_id';
    $handler->display->display_options['fields']['commerce_shipping_service']['label'] = 'Delivery method';
    $handler->display->display_options['fields']['commerce_shipping_service']['element_type'] = '0';
    $handler->display->display_options['fields']['commerce_shipping_service']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['commerce_shipping_service']['element_wrapper_type'] = '0';
    $handler->display->display_options['fields']['commerce_shipping_service']['element_default_classes'] = FALSE;
    $handler->display->display_options['fields']['commerce_shipping_service']['field_api_classes'] = TRUE;
    /* Field: Commerce Customer profile: Address */
    $handler->display->display_options['fields']['commerce_customer_address']['id'] = 'commerce_customer_address';
    $handler->display->display_options['fields']['commerce_customer_address']['table'] = 'field_data_commerce_customer_address';
    $handler->display->display_options['fields']['commerce_customer_address']['field'] = 'commerce_customer_address';
    $handler->display->display_options['fields']['commerce_customer_address']['relationship'] = 'commerce_customer_shipping_profile_id';
    $handler->display->display_options['fields']['commerce_customer_address']['label'] = 'Recipient';
    $handler->display->display_options['fields']['commerce_customer_address']['element_type'] = '0';
    $handler->display->display_options['fields']['commerce_customer_address']['element_wrapper_type'] = '0';
    $handler->display->display_options['fields']['commerce_customer_address']['element_default_classes'] = FALSE;
    $handler->display->display_options['fields']['commerce_customer_address']['click_sort_column'] = 'country';
    $handler->display->display_options['fields']['commerce_customer_address']['settings'] = array(
      'use_widget_handlers' => 0,
      'format_handlers' => array(
        'city-only' => 'city-only',
        'organisation' => 'organisation',
        'name-full' => 'name-full',
      ),
    );
    $handler->display->display_options['fields']['commerce_customer_address']['field_api_classes'] = TRUE;
    /* Field: Commerce Order: Created date */
    $handler->display->display_options['fields']['created']['id'] = 'created';
    $handler->display->display_options['fields']['created']['table'] = 'commerce_order';
    $handler->display->display_options['fields']['created']['field'] = 'created';
    $handler->display->display_options['fields']['created']['label'] = 'Created';
    $handler->display->display_options['fields']['created']['date_format'] = 'custom';
    $handler->display->display_options['fields']['created']['custom_date_format'] = 'd-m-Y';
    /* Field: Commerce Order: Order status */
    $handler->display->display_options['fields']['status']['id'] = 'status';
    $handler->display->display_options['fields']['status']['table'] = 'commerce_order';
    $handler->display->display_options['fields']['status']['field'] = 'status';
    $handler->display->display_options['fields']['status']['label'] = 'Status';
    /* Field: User: E-mail */
    $handler->display->display_options['fields']['mail']['id'] = 'mail';
    $handler->display->display_options['fields']['mail']['table'] = 'users';
    $handler->display->display_options['fields']['mail']['field'] = 'mail';
    $handler->display->display_options['fields']['mail']['relationship'] = 'uid';
    $handler->display->display_options['fields']['mail']['label'] = 'Email';
    $handler->display->display_options['fields']['mail']['exclude'] = TRUE;
    $handler->display->display_options['fields']['mail']['link_to_user'] = '0';
    /* Field: Commerce Order: Operations links (Dropbutton) */
    $handler->display->display_options['fields']['operations_dropbutton']['id'] = 'operations_dropbutton';
    $handler->display->display_options['fields']['operations_dropbutton']['table'] = 'views_entity_commerce_order';
    $handler->display->display_options['fields']['operations_dropbutton']['field'] = 'operations_dropbutton';
    $handler->display->display_options['fields']['operations_dropbutton']['label'] = 'Operations';
    $handler->display->display_options['fields']['operations_dropbutton']['add_destination'] = 1;
    $handler->display->display_options['defaults']['filter_groups'] = FALSE;
    $handler->display->display_options['defaults']['filters'] = FALSE;
    /* Filter criterion: Global: Combine fields filter */
    $handler->display->display_options['filters']['combine']['id'] = 'combine';
    $handler->display->display_options['filters']['combine']['table'] = 'views';
    $handler->display->display_options['filters']['combine']['field'] = 'combine';
    $handler->display->display_options['filters']['combine']['operator'] = 'contains';
    $handler->display->display_options['filters']['combine']['group'] = 1;
    $handler->display->display_options['filters']['combine']['exposed'] = TRUE;
    $handler->display->display_options['filters']['combine']['expose']['operator_id'] = 'combine_op';
    $handler->display->display_options['filters']['combine']['expose']['operator'] = 'combine_op';
    $handler->display->display_options['filters']['combine']['expose']['identifier'] = 'combine';
    $handler->display->display_options['filters']['combine']['expose']['remember_roles'] = array(
      2 => '2',
      1 => 0,
      3 => 0,
    );
    $handler->display->display_options['filters']['combine']['fields'] = array(
      'order_number' => 'order_number',
      'commerce_customer_address' => 'commerce_customer_address',
      'mail' => 'mail',
    );
    /* Filter criterion: Commerce Line item: Shipping service (commerce_shipping_service) */
    $handler->display->display_options['filters']['commerce_shipping_service_value']['id'] = 'commerce_shipping_service_value';
    $handler->display->display_options['filters']['commerce_shipping_service_value']['table'] = 'field_data_commerce_shipping_service';
    $handler->display->display_options['filters']['commerce_shipping_service_value']['field'] = 'commerce_shipping_service_value';
    $handler->display->display_options['filters']['commerce_shipping_service_value']['relationship'] = 'commerce_line_items_line_item_id';
    $handler->display->display_options['filters']['commerce_shipping_service_value']['value'] = array(
      'bpost_home' => 'bpost_home',
      'bpost_different_address' => 'bpost_different_address',
      'bpost_postoffice_postpoint' => 'bpost_postoffice_postpoint',
      'bpost_world' => 'bpost_world',
      'bpost_bpack' => 'bpost_bpack',
    );
    $handler->display->display_options['filters']['commerce_shipping_service_value']['group'] = 1;
    /* Filter criterion: Commerce Order: Order state */
    $handler->display->display_options['filters']['state']['id'] = 'state';
    $handler->display->display_options['filters']['state']['table'] = 'commerce_order';
    $handler->display->display_options['filters']['state']['field'] = 'state';
    $handler->display->display_options['filters']['state']['value'] = $commerce_bpost_settings['mapping']['open_status'];
    /* Filter criterion: Commerce Order: Order type */
    $handler->display->display_options['filters']['type']['id'] = 'type';
    $handler->display->display_options['filters']['type']['table'] = 'commerce_order';
    $handler->display->display_options['filters']['type']['field'] = 'type';
    $handler->display->display_options['filters']['type']['value'] = array(
      'bpost' => 'bpost',
    );

    /* Display: bpost treated orders */
    $handler = $views['commerce_backoffice_orders']->new_display('page', 'bpost treated orders', 'bpost_treated_orders');
    $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
    $handler->display->display_options['defaults']['access'] = FALSE;
    $handler->display->display_options['access']['type'] = 'commerce_bpost';
    $handler->display->display_options['defaults']['relationships'] = FALSE;
    $handler->display->display_options['path'] = 'admin/commerce/orders/bpost-orders/treated';
    $handler->display->display_options['menu']['type'] = 'tab';
    $handler->display->display_options['menu']['title'] = 'Treated';
    $handler->display->display_options['menu']['weight'] = '-8';
    $handler->display->display_options['menu']['context'] = 0;
    $handler->display->display_options['menu']['context_only_inline'] = 0;
    $handler->display->display_options['tab_options']['type'] = 'normal';
    $handler->display->display_options['tab_options']['title'] = 'Treated';
    $handler->display->display_options['tab_options']['description'] = 'Manage orders in the store.';
    $handler->display->display_options['tab_options']['weight'] = '';
    $handler->display->display_options['tab_options']['name'] = 'management';
    /* Relationship: Commerce Order: Referenced customer profile */
    $handler->display->display_options['relationships']['commerce_customer_shipping_profile_id']['id'] = 'commerce_customer_shipping_profile_id';
    $handler->display->display_options['relationships']['commerce_customer_shipping_profile_id']['table'] = 'field_data_commerce_customer_shipping';
    $handler->display->display_options['relationships']['commerce_customer_shipping_profile_id']['field'] = 'commerce_customer_shipping_profile_id';
    $handler->display->display_options['relationships']['commerce_customer_shipping_profile_id']['label'] = 'Shipping information';
    /* Relationship: Commerce Order: Owner */
    $handler->display->display_options['relationships']['uid']['id'] = 'uid';
    $handler->display->display_options['relationships']['uid']['table'] = 'commerce_order';
    $handler->display->display_options['relationships']['uid']['field'] = 'uid';
    /* Relationship: Commerce Order: Referenced line items */
    $handler->display->display_options['relationships']['commerce_line_items_line_item_id']['id'] = 'commerce_line_items_line_item_id';
    $handler->display->display_options['relationships']['commerce_line_items_line_item_id']['table'] = 'field_data_commerce_line_items';
    $handler->display->display_options['relationships']['commerce_line_items_line_item_id']['field'] = 'commerce_line_items_line_item_id';
    $handler->display->display_options['relationships']['commerce_line_items_line_item_id']['required'] = TRUE;
    $handler->display->display_options['defaults']['fields'] = FALSE;
    /* Field: Bulk operations: Commerce Order */
    $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
    $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'commerce_order';
    $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
    $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
    $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
    $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
    $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
    $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '50';
    $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
      'action::commerce_bpost_print_label' => array(
        'selected' => 1,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'action::commerce_bpost_tracking_mail' => array(
        'selected' => 1,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'action::commerce_bpost_create_retour' => array(
        'selected' => 1,
        'postpone_processing' => 0,
        'skip_confirmation' => 1,
        'override_label' => 0,
        'label' => '',
      ),
      'action::commerce_bpost_unlist_order' => array(
        'selected' => 1,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'action::commerce_bpost_cancel_order' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'action::views_bulk_operations_delete_item' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 1,
        'label' => 'Delete order',
      ),
      'action::views_bulk_operations_delete_revision' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'action::views_bulk_operations_script_action' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'action::commerce_bpost_mark_as_treated' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'action::views_bulk_operations_modify_action' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
        'settings' => array(
          'show_all_tokens' => 1,
          'display_values' => array(
            '_all_' => '_all_',
          ),
        ),
      ),
      'action::views_bulk_operations_argument_selector_action' => array(
        'selected' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
        'settings' => array(
          'url' => '',
        ),
      ),
      'rules_component::commerce_shipping_service_bpost_bpack' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'rules_component::commerce_shipping_service_bpost_home' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'rules_component::commerce_shipping_service_bpost_postoffice_postpoint' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'rules_component::commerce_shipping_service_bpost_world' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'action::system_send_email_action' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'rules_component::rules_commerce_order_status_canceled' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'rules_component::rules_commerce_order_status_cart' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'rules_component::rules_order_status_checkout_checkout' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'rules_component::rules_order_status_checkout_complete' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'rules_component::rules_order_status_checkout_payment' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'rules_component::rules_order_status_checkout_review' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'rules_component::rules_order_status_checkout_shipping' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'rules_component::rules_commerce_order_status_completed' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'rules_component::rules_commerce_order_status_pending' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
      'rules_component::rules_commerce_order_status_processing' => array(
        'selected' => 0,
        'postpone_processing' => 0,
        'skip_confirmation' => 0,
        'override_label' => 0,
        'label' => '',
      ),
    );
    /* Field: Commerce Order: Display a pdf icon if label available */
    $handler->display->display_options['fields']['bpost_pdf_icon']['id'] = 'bpost_pdf_icon';
    $handler->display->display_options['fields']['bpost_pdf_icon']['table'] = 'commerce_order';
    $handler->display->display_options['fields']['bpost_pdf_icon']['field'] = 'bpost_pdf_icon';
    $handler->display->display_options['fields']['bpost_pdf_icon']['label'] = 'Label';
    $handler->display->display_options['fields']['bpost_pdf_icon']['element_label_colon'] = FALSE;
    /* Field: Commerce Order: Order number */
    $handler->display->display_options['fields']['order_number']['id'] = 'order_number';
    $handler->display->display_options['fields']['order_number']['table'] = 'commerce_order';
    $handler->display->display_options['fields']['order_number']['field'] = 'order_number';
    $handler->display->display_options['fields']['order_number']['label'] = 'Order n°';
    /* Field: Commerce Line item: Shipping service */
    $handler->display->display_options['fields']['commerce_shipping_service']['id'] = 'commerce_shipping_service';
    $handler->display->display_options['fields']['commerce_shipping_service']['table'] = 'field_data_commerce_shipping_service';
    $handler->display->display_options['fields']['commerce_shipping_service']['field'] = 'commerce_shipping_service';
    $handler->display->display_options['fields']['commerce_shipping_service']['relationship'] = 'commerce_line_items_line_item_id';
    $handler->display->display_options['fields']['commerce_shipping_service']['label'] = 'Delivery method';
    $handler->display->display_options['fields']['commerce_shipping_service']['element_type'] = '0';
    $handler->display->display_options['fields']['commerce_shipping_service']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['commerce_shipping_service']['element_wrapper_type'] = '0';
    $handler->display->display_options['fields']['commerce_shipping_service']['element_default_classes'] = FALSE;
    $handler->display->display_options['fields']['commerce_shipping_service']['field_api_classes'] = TRUE;
    /* Field: Commerce Customer profile: Address */
    $handler->display->display_options['fields']['commerce_customer_address']['id'] = 'commerce_customer_address';
    $handler->display->display_options['fields']['commerce_customer_address']['table'] = 'field_data_commerce_customer_address';
    $handler->display->display_options['fields']['commerce_customer_address']['field'] = 'commerce_customer_address';
    $handler->display->display_options['fields']['commerce_customer_address']['relationship'] = 'commerce_customer_shipping_profile_id';
    $handler->display->display_options['fields']['commerce_customer_address']['label'] = 'Recipient';
    $handler->display->display_options['fields']['commerce_customer_address']['element_type'] = '0';
    $handler->display->display_options['fields']['commerce_customer_address']['element_wrapper_type'] = '0';
    $handler->display->display_options['fields']['commerce_customer_address']['element_default_classes'] = FALSE;
    $handler->display->display_options['fields']['commerce_customer_address']['click_sort_column'] = 'country';
    $handler->display->display_options['fields']['commerce_customer_address']['settings'] = array(
      'use_widget_handlers' => 0,
      'format_handlers' => array(
        'city-only' => 'city-only',
        'organisation' => 'organisation',
        'name-full' => 'name-full',
      ),
    );
    $handler->display->display_options['fields']['commerce_customer_address']['field_api_classes'] = TRUE;
    /* Field: Commerce Order: Created date */
    $handler->display->display_options['fields']['created']['id'] = 'created';
    $handler->display->display_options['fields']['created']['table'] = 'commerce_order';
    $handler->display->display_options['fields']['created']['field'] = 'created';
    $handler->display->display_options['fields']['created']['label'] = 'Created';
    $handler->display->display_options['fields']['created']['date_format'] = 'custom';
    $handler->display->display_options['fields']['created']['custom_date_format'] = 'd-m-Y';
    /* Field: Commerce Order: Order status */
    $handler->display->display_options['fields']['status']['id'] = 'status';
    $handler->display->display_options['fields']['status']['table'] = 'commerce_order';
    $handler->display->display_options['fields']['status']['field'] = 'status';
    $handler->display->display_options['fields']['status']['label'] = 'Status';
    /* Field: User: E-mail */
    $handler->display->display_options['fields']['mail']['id'] = 'mail';
    $handler->display->display_options['fields']['mail']['table'] = 'users';
    $handler->display->display_options['fields']['mail']['field'] = 'mail';
    $handler->display->display_options['fields']['mail']['relationship'] = 'uid';
    $handler->display->display_options['fields']['mail']['label'] = 'Email';
    $handler->display->display_options['fields']['mail']['exclude'] = TRUE;
    $handler->display->display_options['fields']['mail']['link_to_user'] = '0';
    /* Field: Commerce Order: Operations links (Dropbutton) */
    $handler->display->display_options['fields']['operations_dropbutton']['id'] = 'operations_dropbutton';
    $handler->display->display_options['fields']['operations_dropbutton']['table'] = 'views_entity_commerce_order';
    $handler->display->display_options['fields']['operations_dropbutton']['field'] = 'operations_dropbutton';
    $handler->display->display_options['fields']['operations_dropbutton']['label'] = 'Operations';
    $handler->display->display_options['fields']['operations_dropbutton']['add_destination'] = 1;
    $handler->display->display_options['defaults']['filter_groups'] = FALSE;
    $handler->display->display_options['defaults']['filters'] = FALSE;
    /* Filter criterion: Global: Combine fields filter */
    $handler->display->display_options['filters']['combine']['id'] = 'combine';
    $handler->display->display_options['filters']['combine']['table'] = 'views';
    $handler->display->display_options['filters']['combine']['field'] = 'combine';
    $handler->display->display_options['filters']['combine']['operator'] = 'contains';
    $handler->display->display_options['filters']['combine']['group'] = 1;
    $handler->display->display_options['filters']['combine']['exposed'] = TRUE;
    $handler->display->display_options['filters']['combine']['expose']['operator_id'] = 'combine_op';
    $handler->display->display_options['filters']['combine']['expose']['operator'] = 'combine_op';
    $handler->display->display_options['filters']['combine']['expose']['identifier'] = 'combine';
    $handler->display->display_options['filters']['combine']['expose']['remember_roles'] = array(
      2 => '2',
      1 => 0,
      3 => 0,
    );
    $handler->display->display_options['filters']['combine']['fields'] = array(
      'order_number' => 'order_number',
      'commerce_customer_address' => 'commerce_customer_address',
      'mail' => 'mail',
    );
    /* Filter criterion: Commerce Line item: Shipping service (commerce_shipping_service) */
    $handler->display->display_options['filters']['commerce_shipping_service_value']['id'] = 'commerce_shipping_service_value';
    $handler->display->display_options['filters']['commerce_shipping_service_value']['table'] = 'field_data_commerce_shipping_service';
    $handler->display->display_options['filters']['commerce_shipping_service_value']['field'] = 'commerce_shipping_service_value';
    $handler->display->display_options['filters']['commerce_shipping_service_value']['relationship'] = 'commerce_line_items_line_item_id';
    $handler->display->display_options['filters']['commerce_shipping_service_value']['value'] = array(
      'bpost_home' => 'bpost_home',
      'bpost_different_address' => 'bpost_different_address',
      'bpost_postoffice_postpoint' => 'bpost_postoffice_postpoint',
      'bpost_world' => 'bpost_world',
      'bpost_bpack' => 'bpost_bpack',
    );
    $handler->display->display_options['filters']['commerce_shipping_service_value']['group'] = 1;
    /* Filter criterion: Commerce Order: Order state */
    $handler->display->display_options['filters']['state']['id'] = 'state';
    $handler->display->display_options['filters']['state']['table'] = 'commerce_order';
    $handler->display->display_options['filters']['state']['field'] = 'state';
    $handler->display->display_options['filters']['state']['value'] = $commerce_bpost_settings['mapping']['treated_status'];
    /* Filter criterion: Commerce Order: Order type */
    $handler->display->display_options['filters']['type']['id'] = 'type';
    $handler->display->display_options['filters']['type']['table'] = 'commerce_order';
    $handler->display->display_options['filters']['type']['field'] = 'type';
    $handler->display->display_options['filters']['type']['value'] = array(
      'bpost' => 'bpost',
    );
    $translatables['commerce_backoffice_orders'] = array(
      t('bpost open orders'),
      t('Shipping information'),
      t('Line items referenced by commerce_line_items'),
      t('Label'),
      t('<div class="bpost-label-printer"></div>'),
      t('Order n°'),
      t('Delivery method'),
      t('Recipient'),
      t('bpost treated orders'),
    );
  }

}