<?php
/**
 * Template for a list of categories in a tree.
 */

?>
<?php foreach ($items as $voc_name => $voc_items) : ?>

  <div class="list-group">

    <?php foreach ($voc_items as $delta => $term) : ?>
    <?php if ($delta == 0): ?>
    <h3 class="list-group-item"><?php print $voc_name; ?></h3>
    <?php endif; ?>
    <?php print l($term->name . '<span class="badge">' . $term->num_products . '</span>', 'taxonomy/term/' . $term->tid,
        array('html' => TRUE, 'attributes' => array('class' => array('list-group-item')))); ?>
    <?php endforeach; ?>
  </div>
<?php endforeach; ?>