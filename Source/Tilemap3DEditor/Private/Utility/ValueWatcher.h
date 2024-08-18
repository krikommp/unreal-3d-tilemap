#pragma once

template <typename ObjectType>
class TValueWatcher
{
public:
	DECLARE_DELEGATE_OneParam(FOnValueChanged, const ObjectType&);

	TValueWatcher()
		: Value(), OnValueChanged()
	{
	}

	template<typename OtherType>
	TValueWatcher(OtherType&& InValue)
		: Value(static_cast<ObjectType>(InValue)), OnValueChanged()
	{
	}
	
	TValueWatcher(ObjectType&& InValue)
		: Value(MoveTemp(InValue)), OnValueChanged()
	{
	}

	template <class SourceType>
	TValueWatcher(TSharedRef<SourceType> InUserObject, typename FOnValueChanged::template TMethodPtr<SourceType> InMethodPtr)
	: Value(), OnValueChanged(FOnValueChanged::CreateSP(InUserObject, InMethodPtr))
	{
	}
	
	template <class SourceType>
	TValueWatcher(SourceType* InUserObject, typename FOnValueChanged::template TMethodPtr<SourceType> InMethodPtr)
	: Value(), OnValueChanged(FOnValueChanged::CreateSP(InUserObject, InMethodPtr))
	{
	}

	const ObjectType& Get() const { return Value; }
	
	void Bind(const FOnValueChanged& InOnValueChanged)
	{
		OnValueChanged = InOnValueChanged;
	}

	void Bind(FOnValueChanged&& InOnValueChanged)
	{
		OnValueChanged = MoveTemp(InOnValueChanged);
	}

	template < typename... VarTypes >
	void BindStatic( TIdentity_T< typename FOnValueChanged::template TFuncPtr< VarTypes... > > InFuncPtr, VarTypes... Vars )
	{
		OnValueChanged.BindStatic( InFuncPtr, Vars... );
	}

	template <class SourceType>
	void BindRaw(SourceType* InUserObject, typename FOnValueChanged::template TMethodPtr< SourceType > InMethodPtr )
	{
		OnValueChanged.BindRaw(InUserObject, InMethodPtr);
	}
	
	template< class SourceType >
	void Bind( TSharedRef< SourceType > InUserObject, typename FOnValueChanged::template TMethodPtr< SourceType > InMethodPtr )
	{
		OnValueChanged.BindSP( InUserObject, InMethodPtr );
	}
	
	template< class SourceType >
	void Bind( SourceType* InUserObject, typename FOnValueChanged::template TMethodPtr< SourceType > InMethodPtr )
	{
		OnValueChanged.BindSP( InUserObject, InMethodPtr );
	}
	
	template< class SourceType >	
    void BindUObject( SourceType* InUserObject, typename FOnValueChanged::template TMethodPtr< SourceType > InMethodPtr )
    {
    	OnValueChanged.BindUObject( InUserObject, InMethodPtr );
    }
	
	template< class SourceType >
	void BindUFunction( SourceType* InUserObject, const FName& InFunctionName )
	{
		OnValueChanged.BindUFunction(InUserObject, InFunctionName);
	}
	
	bool IsBound() const
	{
		return OnValueChanged.IsBound();
	}

	UE_NODISCARD const FOnValueChanged& GetBinding() const
	{
		return OnValueChanged;
	}

	template < class SourceType >
	void Unbind( SourceType* InUserObject )
	{
		if (OnValueChanged.IsBoundToObject(InUserObject))
		{
			OnValueChanged.Unbind();
		}
	}

	void Unbind()
	{
		OnValueChanged.Unbind();
	}

	TValueWatcher& operator=(ObjectType&& InValue)
	{
		Value = MoveTemp(InValue);
		OnValueChanged.ExecuteIfBound(Value);
		return *this;
	}

	template <typename OtherType>
	TValueWatcher& operator=(OtherType&& InValue)
	{
		Value = static_cast<ObjectType>(InValue);
		OnValueChanged.ExecuteIfBound(Value);
		return *this;
	}

private:
	mutable ObjectType Value;
	FOnValueChanged OnValueChanged;
};