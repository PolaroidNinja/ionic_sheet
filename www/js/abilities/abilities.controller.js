(function(){
    angular.module('character.abilities')
    .controller('abilitiesCTRL', abilitiesCTRL);
    
    function abilitiesCTRL($scope, $stateParams, charactersFactory, classesFactory, $ionicModal, $ionicActionSheet, TEMPLATES) {
        var abilityVM = this;
        
        abilityVM.character = charactersFactory.getCharacterById($stateParams.characterId);
        
        abilityVM.openModal = function(modalType) {
            $ionicModal.fromTemplateUrl(TEMPLATES.MODALS[modalType], {
                scope: $scope,
                animation: 'slide-in-up'
            }).then(function(modal) {
                $scope.modal = modal;
                $scope.modal.show();
            });
        }
        
        abilityVM.addAbility = function(ability) {
            var uid = charactersFactory.generateUID();
            var abilityObj = {
                id: uid,
                name: ability.name,
                description: ability.description,
                order: abilityVM.character.abilities.length || 0
            };
            abilityVM.character.abilities.push(abilityObj);
            charactersFactory.saveCharacter(abilityVM.character);
            abilityVM.closeAbilityModal();
        }
        
        abilityVM.closeAbilityModal = function() {
            $scope.modal.hide();
        }
        
        abilityVM.reorderItem = function(ability, fromIndex, toIndex) {
            abilityVM.character.abilities.splice(fromIndex,1);
            abilityVM.character.abilities.splice(toIndex,0,ability);
            charactersFactory.saveCharacter(abilityVM.character);
        }
        
        abilityVM.editCard = function(ability, editorTemplate, index) {
            abilityVM.editing = ability;
            var hideSheet = $ionicActionSheet.show({
                titleText: abilityVM.editing.name,
                cancelText: "Cancel",
                destructiveText: "Delete",
                destructiveButtonClicked: function() {
                    $ionicActionSheet.show({
                        titleText: "Confirm Deleting " + abilityVM.editing.name,
                        destructiveText: "Delete",
                        destructiveButtonClicked: function() {
                            abilityVM.character.abilities.splice(index, 1);
                            charactersFactory.saveCharacter(abilityVM.character);
                            return true;
                        },
                        cancelText: "Cancel"
                    });
                
                    return true;
                },
                buttons: [
                    {text: "Edit"},
                    {text: "Reorder"}
                ],
                buttonClicked: function(index) {
                    switch(index){
                        case 0: 
                            abilityVM.openModal(editorTemplate);
                            break;
                        case 1:
                            abilityVM.reorder = true;
                            break;
                    }
                    
                    return true;
                }
            });
        }
        
        return abilityVM;
    }
})()