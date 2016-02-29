(function(){
    angular.module('sheet')
    .filter('orderObjectBy', orderObjectBy);
    
    ////////////////////
    
    function orderObjectBy () {
      return function(input, attribute) {
        console.log(input, attribute);
          if (!angular.isObject(input)) return input;
          var array = [];
          for(var objectKey in input) {
              input[objectKey].key = objectKey;
              array.push(input[objectKey]);
          }
      
          array.sort(function(a, b){
              a = parseInt(a[attribute]);
              b = parseInt(b[attribute]);
              return a - b;
          });
          return array;
       };
    }

})();