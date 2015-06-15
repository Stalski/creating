
var Drupal = Drupal || {};

(function($, Drupal){
  "use strict";

  Drupal.behaviors.creatingInit = {
    attach: function(context) {

      // Add spinner to the amount widget.
      $('.form-item-quantity .form-text').spinner({ min: 1, max: 100 });

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