(function() {
    
    angular.module('sheet')
    .directive('preventDrag', function($ionicGesture, $ionicSlideBoxDelegate) {
      return {
        restrict :  'A',
    
        link : function(scope, elem, attrs, e) {
          var reportEvent = function (e){
            $ionicSlideBoxDelegate.enableSlide(e.type === 'release');
          };
    
          $ionicGesture.on('touch', reportEvent, elem);
          $ionicGesture.on('release', reportEvent, elem);
        }
      };
    });
    
})();