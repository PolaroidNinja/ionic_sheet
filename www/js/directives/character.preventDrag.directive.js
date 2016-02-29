(function() {
    
    angular.module('sheet')
    .directive('preventDrag', function($ionicGesture, $ionicSlideBoxDelegate) {
      return {
        restrict :  'A',
    
        link : function(scope, elem, attrs, e) {
          var reportEvent = function (e){
    
            if  (e.target.tagName.toLowerCase() == 'input'){
                $ionicSlideBoxDelegate.enableSlide(false);
            }
            else{
                $ionicSlideBoxDelegate.enableSlide(true);
            }
          };
    
    
          $ionicGesture.on('drag', reportEvent, elem);
        }
      };
    });
    
})();