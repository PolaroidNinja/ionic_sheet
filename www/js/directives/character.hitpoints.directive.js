(function() {
    
    angular.module('sheet')
    .directive('hitpoints', hitpoints);
    
    /////////////////////////////
    
    function hitpoints () {
        return {
            "restrict": "E",
            "controller": hpCTRL,
            "controllerAs": "hitPointVM",
            "templateUrl": "templates/hitpoints.html"
        }
        
        function hpCTRL($scope, charactersFactory) {
            var vm = this;

            return vm;
        }
    }
    
})();