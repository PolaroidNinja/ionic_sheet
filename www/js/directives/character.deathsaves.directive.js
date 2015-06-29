(function() {
    
    angular.module('sheet')
    .directive('deathSaves', deathSaves);
    
    /////////////////////////////
    
    function deathSaves () {
        return {
            "restrict": "E",
            "controller": deathSavesCTRL,
            "controllerAs": "deathSavesVM",
            "templateUrl": "templates/deathsaves.html"
        }
        
        function deathSavesCTRL ($scope, charactersFactory) {
            var deathSavesVM = this;
            
            deathSavesVM.open = true;

            return deathSavesVM;
        }
    }
    
})();