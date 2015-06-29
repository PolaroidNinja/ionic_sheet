(function() {
    
    angular.module('sheet')
    .controller('characterCTRL', characterCTRL);
    
    /////////////////////////
    
    function characterCTRL ($scope, $stateParams, charactersFactory, classesFactory) {
        var vm = this;
        
        vm.character = charactersFactory.getCharacterById($stateParams.characterId);
        vm.charClasses = classesFactory.data;
       
        console.log(vm.charClasses);
        vm.editMode = true;
        
        $scope.$watch(function() { return vm.editMode; }, function() {
            if(typeof character !== "undefined" && character.combat.hp.current == null) {
                character.combat.hp.current = character.combat.hp.max;
            }
           charactersFactory.saveCharacter(vm.character);
        });
        
        vm.modifier = function(score) {
            var scoreInt = parseInt(score);
            return Math.floor((scoreInt - 10) / 2);
        }
        
        return vm;
    }
})();