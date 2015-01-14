/* vim: set ts=2 sw=2 sts=2 et: */

/**
 * Main controller
 */

(function ($) {

Drupal.behaviors.lc3CleanFloatableBox = {
  attach: function (context, settings) {

    // Float button box controller
    $('.floatable-box', context).each(
      function() {
        var elm = $(this);

        // Fix width
        elm.css('width', elm.width() + 'px');

        // Create dump element
        var dump = document.createElement('div');
        dump.className = 'float-box-dump';
        dump = $(dump);
        dump
          .css(
            {
              width: elm.width() + 'px',
              height: elm.height() + 'px'
            }
          )
          .hide();
        elm.after(dump);

        // Calculate limit
        var bottomHeight = elm.height() + 20;
        var topLimit = Math.round(elm.position().top + bottomHeight);

        var scrollHandler = function()
        {
          var showAsFloat = topLimit > ($(document).scrollTop() + $(window).height());

          if ('undefined' == typeof(elm.get(0).showAsFloat) || showAsFloat != elm.get(0).showAsFloat) {

            // State is changed
            elm.get(0).showAsFloat = showAsFloat;

            if (showAsFloat) {

              // Show as float box
              elm
                .css('left', elm.position().left + 'px')
                .addClass('float-box');
              dump.show();

            } else {

              // Show as static box
              elm.removeClass('float-box');
              dump.hide();
            }
          }
        }

        $(document).scroll(scrollHandler);
        scrollHandler();
      }
    );

  }
}

})(jQuery);

;
/* vim: set ts=2 sw=2 sts=2 et: */

/**
 * BlockUI-based popup
 */

// Display a ready-made block element
function lc3_clean_popup_div(id, fade) {
  jQuery.blockUI.defaults.css = {};

  var selector = '#'+id;

  // Disable fade out in Linux versions of Google Chrome because jQuery renders it incorrectly in the browser
  var delay = (lc3_clean_is_linux_chrome() || !fade) ? 0 : 400;

  jQuery.blockUI(
    {
      message: jQuery(selector),
      fadeIn: delay,
      overlayCSS: {
        opacity: 1,
        background: ''
      }
    }
  );

  lc3_clean_postprocess_popup(id);

}

// Display block message
function lc3_clean_popup_message(data, id) {
  jQuery.blockUI.defaults.css = {};

  // Disable fade out in Linux versions of Google Chrome because jQuery renders it incorrectly in the browser
  var delay = lc3_clean_is_linux_chrome() ? 0 : 400;

  jQuery.blockUI(
    {
      message: '<a href="#" class="close-link" onclick="javascript: blockUIPopupClose(); return false;"></a><div class="block-container"><div class="block-subcontainer">' + data + '</div></div>',
      fadeIn: delay,
      overlayCSS: {
        opacity: 0.7
      }
    }
  );

  lc3_clean_postprocess_popup(id);
}


// Close message box
function lc3_clean_close_popup() {

  // Disable fade out in Linux versions of Google Chrome because jQuery renders it incorrectly in the browser
  var delay = lc3_clean_is_linux_chrome() ? 0 : 400;

  jQuery.unblockUI(
    {
      fadeOut: delay
    }
  );
}

// Checks whether it is a Linux Chrome browser
function lc3_clean_is_linux_chrome() {
 return (navigator.userAgent.toLowerCase().indexOf('chrome') > -1) && (navigator.userAgent.toLowerCase().indexOf('linux') > -1);
}



// Postprocess a popup window
function lc3_clean_postprocess_popup(id) {
  // Reposition
  var y = Math.round((jQuery(window).height() - jQuery('.blockMsg').height()) * 3/7);
  var x = Math.round((jQuery(window).width() - jQuery('.blockMsg').width()) / 2);
  if (y<0) {y = 0;}
  if (x<0) {x = 0;}
  jQuery('.blockMsg')
    .css('left', Math.round((jQuery(window).width() - jQuery('.blockMsg').width()) / 2) + 'px')
    .css('top', y+'px')
    .css('z-index', '1200000');

  // Modify overlay
  jQuery('.blockOverlay')
    .attr('title', 'Click to unblock')
    .css('z-index', '1100000')
    .css('cursor', 'pointer')
    .click(lc3_clean_close_popup);

  if (id) {
    var className = 'BlockMsg-' + id;
    jQuery('.blockMsg').addClass(className);
  }
}
;
/* vim: set ts=2 sw=2 sts=2 et: */

/**
 * Top message controller
 */

var MESSAGE_INFO    = 'status';
var MESSAGE_WARNING = 'warning';
var MESSAGE_ERROR   = 'error';

/**
 * Controller
 */

// Constructor
function TopMessages(container) {
  if (!container) {
    return false;
  }

  this.container = jQuery(container).eq(0);
  if (!this.container.length) {
    return false;
  }

  // Add listeners
  var o = this;

  // Close button
  jQuery('a.close', this.container).click(
    function(event) {
      event.stopPropagation();
      o.clearRecords();

      return false;
    }
  ).hover(
    function() {
      jQuery(this).addClass('close-hover');
    },
    function() {
      jQuery(this).removeClass('close-hover');
    }
  );

  // Global event
  if ('undefined' != typeof(window.core)) {
    core.bind(
      'message',
      function(event, data) {
        return o.messageHandler(data.message, data.type);
      }
    );
  }

  // Remove dump items (W3C compatibility)
  jQuery('li.dump', this.container).remove();

  // Fix position: fixed
  this.msie6 = jQuery.browser.msie && parseInt(jQuery.browser.version) < 7;
  if (this.msie6) {
    this.container.css('position', 'absolute');
    this.container.css('border-style', 'solid');
    jQuery('ul', this.container).css('border-style', 'solid');
  }

  // Initial show
  if (!this.isVisible() && jQuery('li', this.container).length) {
    setTimeout(
      function() {
        o.show();

        // Set initial timers
        jQuery('li.status', o.container).each(
          function() {
            o.setTimer(this);
          }
        );
      },
      1000
    );

  } else {

    // Set initial timers
    jQuery('li.status', this.container).each(
      function() {
        o.setTimer(this);
      }
    );
  }
}

/**
 * Properties
 */
TopMessages.prototype.container = null;
TopMessages.prototype.to = null;

TopMessages.prototype.ttl = 10000;

/**
 * Methods
 */

// Check visibility
TopMessages.prototype.isVisible = function() {
  return this.container.css('display') != 'none';
}

// Show widget
TopMessages.prototype.show = function() {
  this.container.slideDown();
}

// Hide widget
TopMessages.prototype.hide = function() {
  this.container.slideUp();
}

// Add record
TopMessages.prototype.addRecord = function(text, type) {
  if (
    !type
    || (MESSAGE_INFO != type && MESSAGE_WARNING != type && MESSAGE_ERROR != type)
  ) {
    type = MESSAGE_INFO; 
  }

  var li = document.createElement('LI');
  li.innerHTML = text;
  li.className = type;
  li.style.display = 'none';

  jQuery('ul', this.container).append(li);

  if (jQuery('li', this.container).length && !this.isVisible()) {
    this.show();
  }

  jQuery(li).slideDown('fast');

  if (type == MESSAGE_INFO) {
    this.setTimer(li);
  }
}

// Clear record
TopMessages.prototype.hideRecord = function(li) {
  if (jQuery('li:not(.remove)', this.container).length == 1) {
    this.clearRecords();

  } else {
    jQuery(li).addClass('remove').slideUp(
      'fast',
      function() {
        jQuery(this).remove();
      }
    );
  }
}

// Clear all records
TopMessages.prototype.clearRecords = function() {
  this.hide();
  jQuery('li', this.container).remove();
}

// Set record timer
TopMessages.prototype.setTimer = function(li) {
  li = jQuery(li).get(0);

  if (li.timer) {
    clearTimeout(li.timer);
    li.timer = false;
  }

  var o = this;
  li.timer = setTimeout(
    function() {
      o.hideRecord(li);
    },
    this.ttl
  );
}

// onmessage event handler
TopMessages.prototype.messageHandler = function(text, type) {
  this.addRecord(text, type);
}

jQuery(document).ready(function () {
  new TopMessages(jQuery('#status-messages'));
});
;
