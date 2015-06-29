(function() {
    
    angular.module('sheet')
    .controller('sheetCTRL', sheetCTRL);
    
    ////////////////////
    
    function sheetCTRL ($state, $location, NEW_CHARACTER_TEMPLATE, charactersFactory, classesFactory, diceRoller) {
        var vm = this;
        vm.characters = null;
        
        _refreshCharacterList();
        
        vm.characterClasses = classesFactory.data;
        
        vm.createCharacter = function() {
            
            var character = charactersFactory.createNewCharacter(NEW_CHARACTER_TEMPLATE);
            _refreshCharacterList();
            $state.go('app.single', {"characterId": character.uid});
        }
        
        vm.deleteCharacter = function(uid) {
            charactersFactory.deleteCharacter(uid);
            _refreshCharacterList();
        }
        
        function _refreshCharacterList () {
            vm.characters = charactersFactory.getCharactersList();
        }
        
        //diceRoller.roll('1d20');
        
        return vm;
    }
    
})();