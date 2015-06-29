(function(){
    
    angular.module('sheet')
    .directive('quickMenu', quickMenu);
    
    /////////////////////////
    
    function quickMenu () {
        return {
            restrict: "E",
            controller: quickMenuCTRL,
            controllerAs: "quickMenuVM",
            templateUrl: "templates/quickMenu.html"
        }
        
        function quickMenuCTRL() {
            var quickMenuVM = this;
            
            return quickMenuVM;
        }
    }
    
})();