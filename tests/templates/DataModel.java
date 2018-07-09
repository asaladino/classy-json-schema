package asaladino.ellucian.EthosApi.Core.Base;

import asaladino.ellucian.EthosApi.Data.Base.BaseModel;
import lombok.Builder;
import lombok.Getter;
import lombok.Setter;

/**
 * {{ description }}
 */
@Builder
public class {{ className }} {% if isDataModel %}extends BaseModel{% else %}{% endif %} {
{% for value in properties %}{% if value/isArray %}
        /**
         * {{ value/description }}
         */
        @Getter
        @Setter
        private List<{% if value/isString %}String{% else %}{{ value/type }}{% endif %}> {{ value/variableName }};
    {% else %}
        /**
         * {{ value/description }}
         */
        @Getter
        @Setter{% if value/isUnknownObject %}
        private Object {{ value/variableName }};{% else %}
        private {% if value/isString %}String{% else %}{{ value/type }}{% endif %} {{ value/variableName }};
    {% endif %}{% endif %}{% endfor %}
}