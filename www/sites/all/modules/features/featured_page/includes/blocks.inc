<?php

/**
 * @file
 * Blocks for featured page.
 */

/**
 * Render a block as header for featured pages in a carousel.
 */
function _feature_page_header_block() {

  $block = array();

  $block['title'] = '';

  $query = db_select('node', 'n');
  $query->innerJoin("field_data_field_page_type", "fpt", "fpt.entity_id = n.nid AND fpt.entity_type = 'node' AND fpt.bundle = 'featured_page' ");
  $query->fields('n', array('nid', 'title'));
  $query->condition('n.status', '1');
  $query->condition('n.type', 'featured_page');
  $query->condition('fpt.field_page_type_value', 'featured_header');
  $query->range(0, 10);
  $result = $query->execute();

  $items = array();
  foreach ($result as $row) {
    $node = node_load($row->nid);

    $link_items = field_get_items('node', $node, 'field_link');
    if ($link_items[0]['url'] == "node/[node:nid]") {
      $link_items[0]['url'] = 'node/' . $row->nid;
    }
    $image_items = field_get_items('node', $node, 'field_bg_image');
    $body_items = field_get_items('node', $node, 'field_header_text');

    $items[] = array(
      'title' => $node->title,
      'message' => $body_items[0]['safe_value'],
      'link' => l($link_items[0]['title'], $link_items[0]['url'], array(
        'attributes' => array('role' => 'button', 'class' => array('btn', 'btn-lg', 'btn-primary')),
      )),
      'image' => theme('image', array('path' => $image_items[0]['uri'])),
    );
  }

  $build = array(
    '#theme' => 'featured_page_header_carousel',
    '#items' => $items,
  );

  if (!empty($items)) {
    $block['content'] = drupal_render($build);
  }

  return $block;

}
