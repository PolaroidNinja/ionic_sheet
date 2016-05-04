(function() {
    
    angular.module('sheet')
    .controller('characterCTRL', characterCTRL);
    
    /////////////////////////
    
    function characterCTRL ($scope, $stateParams, charactersFactory, classesFactory, $ionicModal, $ionicActionSheet, TEMPLATES) {
        var vm = this;
        
        vm.character = charactersFactory.getCharacterById($stateParams.characterId);
        vm.charClasses = classesFactory.data;
        vm.currentSlide;
       
        vm.editMode = true;
        vm.ability = {
            reorder: false
        };
        
        
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
        
        // vm.openModal = function(modalType) {
        //     $ionicModal.fromTemplateUrl(TEMPLATES.MODALS[modalType], {
        //         scope: $scope,
        //         animation: 'slide-in-up'
        //     }).then(function(modal) {
        //         $scope.modal = modal;
        //         $scope.modal.show();
        //     });
        // }
        
        // vm.addAbility = function(ability) {
        //     var uid = charactersFactory.generateUID();
        //     var abilityObj = {
        //         id: uid,
        //         name: ability.name,
        //         description: ability.description,
        //         order: vm.character.abilities.length || 0
        //     };
        //     vm.character.abilities.push(abilityObj);
        //     vm.closeAbilityModal();
        // }
        
        // vm.closeAbilityModal = function() {
        //     $scope.modal.hide();
        // }
        
        // vm.reorderItem = function(ability, fromIndex, toIndex) {
        //     vm.character.abilities.splice(fromIndex,1);
        //     vm.character.abilities.splice(toIndex,0,ability);
        //     charactersFactory.saveCharacter(vm.character);
        // }
        
        // vm.editCard = function(ability, editorTemplate) {
        //     vm.editing = ability;
        //     var hideSheet = $ionicActionSheet.show({
        //         titleText: vm.editing.name,
        //         cancelText: "Cancel",
        //         destructiveText: "Delete",
        //         destructiveButtonClicked: function() {
        //             $ionicActionSheet.show({
        //                 titleText: "Confirm Deleting " + vm.editing.name,
        //                 destructiveText: "Delete",
        //                 destructiveButtonClicked: function() {
        //                     delete vm.character[type][uid];
        //                     return true;
        //                 },
        //                 cancelText: "Cancel"
        //             });
                
        //             return true;
        //         },
        //         buttons: [
        //             {text: "Edit"},
        //             {text: "Reorder"}
        //         ],
        //         buttonClicked: function(index) {
        //             switch(index){
        //                 case 0: 
        //                     vm.openModal(editorTemplate);
        //                     break;
        //                 case 1:
        //                     vm.ability.reorder = true;
        //                     break;
        //             }
                    
        //             return true;
        //         }
        //     });
        // }
        
        return vm;
    }
})();