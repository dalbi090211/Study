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

[RequireComponent(typeof(CapsuleCollider2D))]
public class TestCharacterRigid2D : MonoBehaviour
{
    [SerializeField] private CapsuleCollider2D capsule;
    [SerializeField] private float GravitySpeed = 0.0f;

    private Vector2 Velocity = Vector2.zero;   //이전 속력
    [SerializeField] private float dragCoefficient = 0.2f;   //저항계수
    public event Action OnGroundIn;
    public event Action OnGroundOut;
    public event Action OnAirIn;
    public event Action OnAirOut;

    public event VelChangeHandler OnCalcVelocity;

    [SerializeField] private ContactFilter2D GroundContactFilter;   //충돌을 허용할 레이어 목록
    private GroundStateType GroundState = GroundStateType.Ground;
    [SerializeField] private float skinWidth = 1.0f;    //스프라이트 별로 다르게 적용되는 바닥 보정거리
    private float groundProbeDistance  = 0.2f;  //일괄로 적용되는 바닥 보정거리
    private float acceptFloorDistance = 0.1f;

    private void Awake() {
        if(capsule == null) capsule = GetComponent<CapsuleCollider2D>();

        OnGroundIn -= OnGroundLanded;
        OnGroundIn += OnGroundLanded;
    }

    private void FixedUpdate(){
        applyRealPhysics();
        applyFakePhysics();

        // rb.MovePosition(rb.position + FinalVelocity);
    }

    private void applyRealPhysics()
    {
        applyMoveCommand();
        applyGroundState();
        
        transform.position += (Vector3)Velocity;
    }

    private void applyFakePhysics()
    {
        
    }

    private void applyMoveCommand(){
        foreach (var handler in OnCalcVelocity.GetInvocationList())
        {
            Vector2 resistance = Velocity * dragCoefficient;
            ((VelChangeHandler)handler)(ref Velocity, resistance);
        }
    }

    private void OnGroundLanded(){
        OnAirOut?.Invoke();

        Velocity.y = 0.0f;
    }
    
    private void applyGroundState(){
        switch(getGroundState){
            case GroundStateType.Ground : 
                
                break;

            case GroundStateType.Air : 
                Velocity.y -= Time.deltaTime * GravitySpeed;
                break;
        }
    }

    private GroundStateType getGroundState{
        get{
            if(FindGround){
                if(GroundState != GroundStateType.Ground) OnGroundIn?.Invoke();
                GroundState = GroundStateType.Ground;
            }
            else{
                if(GroundState != GroundStateType.Air) OnAirIn?.Invoke();
                GroundState = GroundStateType.Air;
            }
            return GroundState;
        }
    }

    private bool FindGround{
        get{
            List<RaycastHit2D> hits = new List<RaycastHit2D>(16);

            var tr = capsule.transform;
            Vector2 scale = new Vector2(Mathf.Abs(tr.localScale.x), Mathf.Abs(tr.localScale.y));
            Physics2D.CapsuleCast(
                capsule.bounds.center, 
                capsule.size * scale, 
                capsule.direction, 
                0.0f, 
                Vector2.down, 
                GroundContactFilter, 
                hits, 
                groundProbeDistance
            );

            foreach (var hit in hits){
                if(hit.normal.y > 0.6f && hit.distance < acceptFloorDistance) return true;
            }

            return false;
        }
    }
}
