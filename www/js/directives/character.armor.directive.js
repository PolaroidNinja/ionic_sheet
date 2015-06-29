(function() {
    
    angular.module('sheet')
    .directive('armorClass', armorClass);
    
    /////////////////////////////
    
    function armorClass () {
        return {
            "restrict": "E",
            "controller": armorCTRL,
            "controllerAs": "armorVM",
            "scope": {
              "character": "=",
              "editMode": "="
            },
            "bindToController": true,
            "templateUrl": "templates/armorclass.html"
        }
        
        function armorCTRL($scope, charactersFactory) {
            var armorVM = this;
            armorVM.ACOverride = null;
            calculateAC();
            
            function calculateAC () {
                var baseAC = armorVM.character.combat.ac;
                var dexMod = charactersFactory.getModifier(armorVM.character.stats.dexterity.score);
                armorVM.AC = armorVM.ACOverride || parseInt(baseAC) + parseInt(dexMod); 
            }
            
            $scope.$watch(function(){
                return armorVM.character.stats.dexterity.score;
            }, calculateAC);
            
            $scope.$watch(function(){
                return armorVM.character.combat.ac;
            }, calculateAC);
            
            return armorVM;
        }
    }
    
})();