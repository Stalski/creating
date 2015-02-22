/**
 * @file
 * Script file to handle the display of a google map.
 */

(function ($) {

  Drupal.behaviors.commerceBpost = {
    attach:function (context, settings) {
      $('#' + settings.commerce_bpost_map.id).once(function () {
        $.fn.commerceBpostInitialize(context, settings);
      });
    }
  }

  /**
   * Initialize map.
   */
  $.fn.commerceBpostInitialize = function (context, settings) {

    // Create map
    var mapOptions = {
      center:new google.maps.LatLng(-34.397, 150.644),
      //zoom:settings.commerce_bpost_map.zoom,
      streetViewControl:settings.commerce_bpost_map.street_view_control,
      mapTypeControl:settings.commerce_bpost_map.map_type_control,
      mapTypeId:google.maps.MapTypeId.ROADMAP
    };
    map = new google.maps.Map(document.getElementById(settings.commerce_bpost_map.id), mapOptions);

    // Use by auto-zoom function
    var latlngbounds = new google.maps.LatLngBounds();

    // Center map
    geocoder = new google.maps.Geocoder();

    $.fn.commerceBpostSetHome(settings, latlngbounds);

    // Create markers
    var markers = {};
    var infoWindows = {};
    var markersData = $.parseJSON(settings.commerce_bpost_map.markers);
    for (var i in markersData) {
      var markerData = markersData[i];
      var markerLatLng = new google.maps.LatLng(markerData.coordGeolocalisationLatitude, markerData.coordGeolocalisationLongitude);
      var marker = new google.maps.Marker({
        position:markerLatLng,
        map:map,
        id:markerData.identifiant,
        content_map:markerData.content_map,
        content_top:markerData.content_top,
        icon:markerData.icon
      });
      latlngbounds.extend(markerLatLng);

      // Store the marker so we can access it later.
      markers[markerData.identifiant] = marker;

      // Add InfoWindow for this marker and store it so we can access it later.
      infoWindows[marker.id] = attachInfoWindow(marker, markerData.infoWindow);
    }

    function closeAllInfoWindow() {
      for (var i in infoWindows) {
        infoWindows[i].close();
      }
    }

    // Click point in the list
    $('.points-list input[type=radio]').click(function() {
      var point = this.value.split("|");
      closeAllInfoWindow();
      infoWindows[point[1]].open(markers[point[1]].get('map'), markers[point[1]]);

      // Clear selected parent labels.
      $('.points-list .form-item.selected').removeClass('selected');
      // Get radio buttons list.
      $(this).parent().addClass('selected');
    });

    // Click point on the map
    function attachInfoWindow(marker, message) {
      var infowindow = new google.maps.InfoWindow({
        content:message
      });
      google.maps.event.addListener(marker, 'click', function () {
        closeAllInfoWindow();
        infowindow.open(marker.get('map'), marker);
        // Clear selected parent labels.
        $('.points-list .form-item.selected').removeClass('selected');
        // Get radio buttons list.
        $('.points-list input[type=radio]').each(
          function (key, domElement) {
            if (String(domElement.value) === markersData[marker.id].type.concat('|', marker.id)) {
              // Add class to parent.
              domElement.parentNode.classList.add('selected');
              // Check the found radio box.
              domElement.checked = true;
            }
          }
        );
        // Point to the selected map point.
        var elementSelected = $('.points-list .form-item.selected');
        var container = $('#points-wrapper');
        container.scrollTop(
          elementSelected.offset().top - container.offset().top + container.scrollTop()
        );
      });
      return infowindow;
    }

    // Highlight and select point in points list.
    function selectPoint(element) {
      var input = $('#' + $(element).attr('id') + ' input.select-point');
      var marker_id = input.val();
      var marker = markers[marker_id];
      $('.point-wrapper div.selected').removeClass('selected');
      $(element).addClass('selected');
      input.attr('checked', true);
      $('.point-wrapper').html(marker.content_top);
      info.setContent(marker.content_map);
      info.open(map, marker);
    }
  }

  /**
   * Center map on address
   */
  $.fn.commerceBpostSetHome = function (settings, bounds) {
    geocoder.geocode({ 'address':settings.commerce_bpost_map.address}, function (results, status) {
      if (status == google.maps.GeocoderStatus.OK) {
        map.setCenter(results[0].geometry.location);
        var marker = new google.maps.Marker({
          position:results[0].geometry.location,
          map:map,
          icon:settings.commerce_bpost_map.icons.domicile
        });
        bounds.extend(results[0].geometry.location);
        if (settings.commerce_bpost_map.autozoom) {
          map.fitBounds(bounds);
        }
      }
      else {
        // Use for debug only
        //alert('Geocode was not successful for the following reason: ' + status);
      }
    });
  }

})(jQuery);
