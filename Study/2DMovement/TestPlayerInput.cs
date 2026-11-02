using UnityEngine;
using UnityEngine.InputSystem;

public class TestPlayerInput : MonoBehaviour
{
    [SerializeField] private PlayerInput playerInput;
    [SerializeField] private TestCharacterRigid2D rigid;

    [SerializeField] private float JumpDuration;
    [SerializeField] private AnimationCurve JumpAccelCurve;
    [SerializeField] private float JumpRestTime = 0.2f;
    private float curJumpRestTime = 0.0f;
    private int MaxJumpCount = 2;
    private int CurJumpCount = 0;

    [SerializeField] private bool EnableKoyoteTime = true;
    [SerializeField] private float EnableKoyoteTime = 0.2f;

    private InputAction moveAction;
    private InputAction jumpAction;

    public void Initialize(){
        moveAction = playerInput.actions.FindAction("Player/Move", true);
        jumpAction = playerInput.actions.FindAction("Player/Jump", true);
        playerInput.onActionTriggered += OnAction;

        if(rigid == null)
    }

    private void DeInitialize(){
        playerInput.onActionTriggered -= OnAction;
    }

    private void OnAction(InputAction.CallbackContext context){
        if(context.action == moveAction){
            OnMove(context.ReadValue<Vector2>().x);
        }
        
        if(context.action == jumpAction){
            OnJump();
        }

        if(context.performed){
            Debug.Log("눌린 입력 : " + context.action.name);
        }
    }

    private void OnJump(){
        rigid.AddHorizontal(5.0f);
    }

    private void OnMove(float x){
        rigid.AddVertical(x);
    }

    private bool CanJump(){

    }
}
