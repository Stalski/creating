<?php

/**
 * @file
 * Override the html to bootstrap html.
 *
 * - $rows contains a nested array of rows. Each row contains an array of
 *   columns.
 *
 * @ingroup views_templates
 */
?>
<?php if (!empty($title)) : ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>
<div class="<?php print $class; ?>"<?php print $attributes; ?>>
<?php if (!empty($caption)) : ?>
  <caption><?php print $caption; ?></caption>
<?php endif; ?>

<?php foreach ($rows as $row_number => $columns): ?>
  <div <?php if ($row_classes[$row_number]) { print 'class="' . $row_classes[$row_number] .'"';  } ?>>
    <?php foreach ($columns as $column_number => $item): ?>
    <div <?php if ($column_classes[$row_number][$column_number]) { print 'class="' . $column_classes[$row_number][$column_number] .'"';  } ?>>
      <?php print $item; ?>
    </div>
    <?php endforeach; ?>
  </div>
<?php endforeach; ?>
</div>
