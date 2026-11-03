using System;
using System.Collections.Generic;
using UnityEngine;

public enum GroundStateType{
    Ground,
    Air
}

public enum LocoStateType{  //virtual player 만들어서 애니메이터 연동, enum 위치도 player로 이동
    Walk,
    Run,
    Idle,
    Fall
}

[RequireComponent(typeof(Rigidbody2D), typeof(CapsuleCollider2D))]
public class TestCharacterRigid2D : MonoBehaviour
{
    [SerializeField] private Rigidbody2D rb;
    [SerializeField] private CapsuleCollider2D capsule;
    [SerializeField] private float GravitySpeed = 0.0f;

    private Vector2 FinalVelocity;

    public event Action OnGroundLand;
    public event Action OnAirLand;
    public event Action OnJumpStopped;

    public event VectorChangeHandler OnCalcVelocity;

    [SerializeField] private ContactFilter2D GroundContactFilter;   //충돌을 허용할 레이어 목록
    private GroundStateType GroundState = GroundStateType.Ground;
    [SerializeField] private float skinWidth = 1.0f;    //스프라이트 별로 다르게 적용되는 바닥 보정거리
    private float groundProbeDistance  = 0.2f;  //일괄로 적용되는 바닥 보정거리
    private float acceptFloorDistance = 0.1f;

    private void Awake() {
        if(rb == null)  rb = GetComponent<Rigidbody2D>();
        if(capsule == null) capsule = GetComponent<CapsuleCollider2D>();
    }

    private void FixedUpdate(){
        FinalVelocity = new Vector2(0.0f, 0.0f);
        applyGroundState();
        applyMoveCommand();
        rb.MovePosition(rb.position + FinalVelocity);
    }
    
    private void applyGroundState(){
        switch(getGroundState){
            case GroundStateType.Ground : 
                break;

            case GroundStateType.Air : 
                FinalVelocity.y -= Time.deltaTime * GravitySpeed;
                break;
        }
    }

    private void applyMoveCommand(){
        OnCalcVelocity(ref FinalVelocity);
    }

    private GroundStateType getGroundState{
        get{
            if(FindGround){
                if(GroundState != GroundStateType.Ground) OnGroundLand?.Invoke();
                GroundState = GroundStateType.Ground;
            }
            else{
                if(GroundState != GroundStateType.Air) OnAirLand?.Invoke();
                GroundState = GroundStateType.Air;
            }
            return GroundState;
        }
    }

    private bool FindGround{
        get{
            List<RaycastHit2D> hits = new List<RaycastHit2D>(16);
            capsule.Cast(rb.position, rb.rotation, Vector2.down, GroundContactFilter, hits, skinWidth + groundProbeDistance);
        
            foreach (var hit in hits){
                if(hit.normal.y > 0.6f && hit.distance < acceptFloorDistance) return true;
            }

            return false;
        }
    }
}
