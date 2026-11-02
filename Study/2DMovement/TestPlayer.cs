using UnityEngine;

public class TestPlayer : MonoBehaviour
{
    [SerializeField] TestPlayerInput playerInput;

    private void Awake(){
        if(playerInput == null) playerInput = GetComponent<TestPlayerInput>();
    }

    private void OnEnable(){
        playerInput.Initialize();
    }

    private void OnDisable(){
        playerInput.DeInitialize();
    }

}
