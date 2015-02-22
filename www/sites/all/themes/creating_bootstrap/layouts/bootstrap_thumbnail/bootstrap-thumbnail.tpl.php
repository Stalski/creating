<?php
/**
 * @file
 * Template for a 1 column bootstrap thumbnail with custom content.
 *
 *
 * - $content: An array of content, each item in the array is keyed to one
 *   panel of the layout. This layout supports the following sections:
 *   $content['caption']: The custom content as caption.
 *   $content['thumbnail_image']: the section for the thumbnail image..
 */
?>
<div class="thumbnail">
  <!-- Needed to activate contextual links -->
  <?php if (isset($title_suffix['contextual_links'])): ?>
    <?php print render($title_suffix['contextual_links']); ?>
  <?php endif; ?>
  <?php print $content['thumbnail_image']; ?>
  <div class="caption">
    <?php print $content['caption']; ?>
  </div>
</div>
