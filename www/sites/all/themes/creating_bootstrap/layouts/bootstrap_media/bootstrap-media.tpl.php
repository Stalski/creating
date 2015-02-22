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
<div class="media">
  <div class="media-left">
    <?php print $content['media_left']; ?>
    <?php /*
    <a href="#">
      <img class="media-object" src="..." alt="...">
    </a> */
    ?>
  </div>
  <div class="media-body">
    <?php /*
     <h4 class="media-heading">Media heading</h4>
      */
    ?>
    <?php print $content['media_body']; ?>
  </div>
</div>
