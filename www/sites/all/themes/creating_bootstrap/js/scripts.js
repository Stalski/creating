
var Drupal = Drupal || {};

(function($, Drupal){
  "use strict";

  Drupal.behaviors.creatingInit = {
    attach: function(context) {

      // Add the prev/next behavior to the genericHeader.
      $(context).find('#genericHeader').once('header-carousels', function () {

        $('.carousel-control.left').click(function() {
          $('#genericHeader').carousel('prev');
        });

        $('.carousel-control.right').click(function() {
          $('#genericHeader').carousel('next');
        });

      });
    }
  };


})(jQuery, Drupal);