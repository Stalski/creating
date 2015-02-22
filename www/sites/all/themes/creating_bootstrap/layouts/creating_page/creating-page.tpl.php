<?php
/**
 * @file
 * Template for Creating page.
 *
 * Variables:
 * - $css_id: An optional CSS id to use for the layout.
 * - $content: An array of content, each item in the array is keyed to one
 * panel of the layout. This layout supports the following sections:
 */
?>

<div class="panel-display clearfix <?php if (!empty($classes)) { print $classes; } ?><?php if (!empty($class)) { print $class; } ?>" <?php if (!empty($css_id)) { print "id=\"$css_id\""; } ?>>

  <div class="row container-fluid">
    <div class="col-md-12 panel-panel">
      <div class="panel-panel-inner">
        <?php print $content['featured']; ?>
      </div>
    </div>
  </div>

  <div class="container-fluid">
    <div class="row">
      <div class="col-md-3 panel-panel">
        <div class="panel-panel-inner">
          <?php print $content['sidebar']; ?>
        </div>
      </div>
      <div class="col-md-9 panel-panel">
        <div class="row">
          <div class="col-md-12 panel-panel">
            <?php print $content['contentheader']; ?>
          </div>
        </div>
        <div class="row">
          <div class="col-md-6 panel-panel">
            <?php print $content['contentcolumn1']; ?>
          </div>
          <div class="col-md-6 panel-panel">
            <?php print $content['contentcolumn2']; ?>
          </div>
        </div>
        <div class="row">
          <div class="col-md-12 panel-panel">
            <?php print $content['contentfooter']; ?>
          </div>
        </div>
      </div>
    </div>
  </div>

</div>
