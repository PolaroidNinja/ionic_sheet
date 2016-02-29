(function () {
    
    angular.module('sheet')
    .directive('characterStats', characterStats);
    
    ////////////////////
    
    function characterStats() {
        return {
            restrict: "E",
            scope: {
                'character': "=",
                'editMode': "="
            },
            controller: characterStatCTRL,
            controllerAs: "statsVM",
            bindToController: true,
            templateUrl: "templates/stats.html"
        }
        
        function characterStatCTRL(charactersFactory) {
            var vm = this;
            vm.modifier = charactersFactory.getModifier;
            return vm;
        }
    }
})();