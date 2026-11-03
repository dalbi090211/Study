using UnityEngine;
using UnityEngine.InputSystem;

public class TestPlayerInput : MonoBehaviour
{
    [SerializeField] private PlayerInput playerInput;
    [SerializeField] private TestCharacterRigid2D rigid;

    /*      점프 관련       */
    [SerializeField] private bool EnableKoyoteTime = true;
    [SerializeField] private float MaxKoyoteTime = 0.2f;

    [SerializeField] private float jumpSpeed = 5.0f;
    [SerializeField] private AnimationCurve JumpAccelCurve;
    [SerializeField] private float JumpRestTime = 0.2f; //점프가 연속으로 입력되는 경우 방지
    [SerializeField] private float JumpDuration = 2.0f; //점프의 최대 지속시간, 넘으면 점프 가속 중지
    private float LastJumpTime = 0.0f;
    private int MaxJumpCount = 2;
    private int CurJumpCount = 0;

    /*      이동 관련       */
    [SerializeField] private AnimationCurve RunAccelCurve;
    private bool isRunning = false;
    private bool isMoving = false;
    private int XDir = 0;
    private float CurRunTime = 0.0f;
    [SerializeField] private float MaxRunTime = 2.0f;    //달리기의 속도가 한계에 이르는 데 걸리는 시간
    [SerializeField] private float runSpeed = 5.0f;


    /*      키 바인딩       */
    private InputAction moveAction;
    private InputAction jumpAction;

    public void Initialize(){
        moveAction = playerInput.actions.FindAction("Player/Move", true);
        jumpAction = playerInput.actions.FindAction("Player/Jump", true);
        playerInput.onActionTriggered += OnAction;

        rigid.OnCalcVelocity -= calcMove;
        rigid.OnCalcVelocity += calcMove;

    }

    public void DeInitialize(){
        playerInput.onActionTriggered -= OnAction;

        rigid.OnCalcVelocity -= calcJump;
        rigid.OnCalcVelocity -= calcMove;
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

    private bool canJump(){
        return true;
    }

    private void OnJump(){
        if(canJump()){
            CurJumpCount += 1;
            LastJumpTime = 0.0f;

            rigid.OnCalcVelocity -= calcJump;
            rigid.OnCalcVelocity += calcJump;
        }
    }

    private void OnMove(float x){
        int curPos = (int)x; 
        if(curPos != XDir){
            CurRunTime = 0.0f;
        }
        XDir = curPos;
    }

    private void calcJump(ref Vector2 vec){
        LastJumpTime += Time.deltaTime;
        
        if(LastJumpTime >= JumpDuration){
            rigid.OnCalcVelocity -= calcJump;
            return;
        }

        vec.y += JumpAccelCurve.Evaluate(LastJumpTime / JumpDuration) * Time.deltaTime * jumpSpeed;
    }

    private void calcMove(ref Vector2 vec){
        CurRunTime += Time.deltaTime;
        float t = Mathf.Clamp01(CurRunTime / MaxRunTime);
        vec.x += RunAccelCurve.Evaluate(t) * Time.deltaTime * runSpeed * XDir;
    }
}
